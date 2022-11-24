#include "db-server.hpp"

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h> // For read


#include <stdexcept>
#include <string>
#include <thread>
#include <cstring>
#include <sstream>

#define SERVER_PORT 6969


int DbServer::Utils::ReadSizeFromBuf(unsigned char* byteBuffer, int offset) {
  auto offsetadjusted = byteBuffer;
  int value = int(
    (offsetadjusted[3 + offset]) << 24 |
    (offsetadjusted[2 + offset]) << 16 |
    (offsetadjusted[1 + offset]) << 8 |
    (offsetadjusted[0 + offset])
  );

  return value;
}

std::vector<unsigned char> DbServer::Utils::DataAsVec(unsigned char* byteBuffer, int startPosition, int size) {
  std::vector<unsigned char> res;
  res.insert(res.end(), byteBuffer+startPosition, byteBuffer+startPosition+size);
  return res;
}

void DbServer::Utils::WriteResponse(unsigned char* byteBuffer, const std::string& response, int connection, int bufferSize) {
  std::memset(byteBuffer, 0, bufferSize);
  char respSize = response.size();
  for (int i = 0; i < 4; i++)
    byteBuffer[i] = respSize >> (i * 8); 
  byteBuffer[4] = ' ';
  std::copy(response.begin(), response.end(), byteBuffer+5);
  write(connection, byteBuffer, bufferSize);
}

void DbServer::Utils::WriteVecResponse(unsigned char* byteBuffer, const std::vector<unsigned char>& response, int connection, int bufferSize) {
  std::memset(byteBuffer, 0, bufferSize);
  std::copy(response.begin(), response.end(), byteBuffer);
  write(connection, byteBuffer, bufferSize);
}

DbServer::Db::Db(std::shared_ptr<ConcurMap::MapStore> storage, int p, bool _persist): store(storage), port(p), persist(_persist) {
  int success = Start();
  if (success != 0) {
    logger.LogError("Unable to boot error");
    throw "Unable to boot up server";
  }
}

const std::string DbServer::Db::bufferSizeContradictionResp = "size contradiction";

const std::string DbServer::Db::unknownCommandResp = "Another one";

const std::string DbServer::Db::successResp = "success";

const std::string DbServer::Db::noVal = "";

const std::unordered_map<std::string, DbServer::Commands> DbServer::Db::cmdMap = {
  {"SET", Commands::SET},
  {"GET", Commands::GET},
  {"DEL", Commands::DEL},
  {"ALL", Commands::ALL}
};

// blocking call used to accept incoming connections and handle them in their own thread
int DbServer::Db::Listen() {  
  if (persist) {
    logger.LogInfo("Server setting up persistence");
    DiskPersist persister(store, "../data/");
    persister.Hydrate();
    persister.AsyncPersist();
  }
  
  listening = true;

  logger.LogInfo("Server listening and accepting connections on port " + std::to_string(port));

  while (listening) {
    connection = accept(socketFd, (struct sockaddr*) &cliaddr, (socklen_t*)&addrlen);
    if (connection < 0) {
      logger.LogError("Error accepting connection");
      return -1;
    }

    // handle each connection by passing the buffer down to it's own detached thread
    std::thread requesthandlerthread([&]() -> void {
      logger.LogInfo("Connection recieved!");
      HandleBody(connection);
    });
    requesthandlerthread.detach();
  }

  return 0;
}

DbServer::Db::~Db(){
  Stop();
}

int DbServer::Db::Start() {
  logger.LogInfo("Starting db server");
  int opt = 1;
  socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socketFd) {
    logger.LogError("Server error");
    return -1;
  }

  // Forcefully attaching socket to the port 8080 
  if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
  { 
    logger.LogError("Setsockopt error");
    return -1;
  }

  struct sockaddr_in sockaddr, cliaddr;
  
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;

  // htons is necessary to convert a number to network byte order
  sockaddr.sin_port = htons(port);
  
  auto bindSuccess = ::bind(socketFd, (struct sockaddr*) &sockaddr, sizeof(sockaddr));

  if (bindSuccess < 0) {
    logger.LogError("Unable to bind");
    return -1;
  }

  listenDescriptor = listen(socketFd, 10);
  if (listenDescriptor != 0) {
    logger.LogError("Unable to listen");
    return -1;
  }
  
  logger.LogInfo("Server ready to start listening on port " + std::to_string(port));

  return 0;
}

void DbServer::Db::Stop() {
  logger.LogInfo("Stopping db server");
  listening = false;
  close(listenDescriptor);
  shutdown(socketFd, SHUT_RDWR);
}

void DbServer::Db::HandleBody(int connection) {
  // bufferSize is a const so im not worried about stack overflow
  unsigned char bytebuffer[bufferSize];
  
  read(connection, bytebuffer, bufferSize);
  
  auto cmd = ReadCommandHeader(bytebuffer);

  switch (cmd) {
    case Commands::SET:
      SetHandler(connection, bytebuffer);
      break;
    case Commands::GET:
      GetHandler(connection, bytebuffer);
      break;
    case Commands::DEL:
      DelHandler(connection, bytebuffer);
      break;
    case Commands::ALL:
      AllHandler(connection, bytebuffer);
      break;
    default:
      logger.LogError("Command not found");
      Utils::WriteResponse(bytebuffer, unknownCommandResp, connection, bufferSize);
      break;
  }
  // after we write back a response we can close our connection cutely
  close(connection);
}

DbServer::Commands DbServer::Db::ReadCommandHeader(unsigned char* bytebuffer) {
  // using const to allocate memory
  std::vector<unsigned char> cmdreaderbuf = Utils::DataAsVec(bytebuffer, 0, commandByteSize);

  std::string commandstr(cmdreaderbuf.begin(), cmdreaderbuf.end());
  logger.LogInfo("command decoded from buffer: " + commandstr);
  
  Commands cmd;
  try {
    cmd = cmdMap.at(commandstr);
  }
  catch(const std::exception& e) {
    return Commands::NEG;
  }
  return cmd;
}

/**
 *  SET Request Format: SET KEY_SIZE VAL_SIZE key.... val....
 * Set handler needs to  do validationg that we have valid key size and val size
 * and that it fits in our byte buffer max size
 * */
void DbServer::Db::SetHandler(int connection, unsigned char* bytebuffer) {
  // from bytebuffer contains key and value
  logger.LogInfo("set cmd recieved");

  // we are going to strictly deal with int32 4 bytes in buffer sent 
  // first n bytes (commandByteSize) are taken over to signify command.
  int bufferMemoryTillKeySize = commandByteSize + spaceDelimitter;
  int keyByteSize = Utils::ReadSizeFromBuf(bytebuffer, bufferMemoryTillKeySize);
  logger.LogInfo("key byte size " + std::to_string(keyByteSize));
  
  int bufferMemoryTillValSize = bufferMemoryTillKeySize + sizeof(int) + spaceDelimitter;
  int valByteSize = Utils::ReadSizeFromBuf(bytebuffer, bufferMemoryTillValSize);
  logger.LogInfo("val byte size " + std::to_string(valByteSize));

  // CMD_KEYSIZEBYTES_VALSIZEBYTES_KEY..._VAL...
  int bufferMemoryUsedByMetadata = bufferMemoryTillValSize + sizeof(int) + spaceDelimitter;
  int bufferMemoryToBeUsed = keyByteSize+valByteSize+bufferMemoryUsedByMetadata+spaceDelimitter;

  if (bufferMemoryToBeUsed > bufferSize) {
    Utils::WriteResponse(bytebuffer, bufferSizeContradictionResp, connection, bufferSize);
    return;
  }

  std::vector<unsigned char> key = Utils::DataAsVec(bytebuffer, bufferMemoryUsedByMetadata, keyByteSize);
  
  // store valsize metadata and value
  int bufferOccupiedTillVal = bufferMemoryUsedByMetadata + spaceDelimitter + keyByteSize;

  // create a val buffer that includes valByteSize and val adn delimitter space
  std::vector<unsigned char> val(sizeof(int) + spaceDelimitter + valByteSize, 0);
  std::vector<unsigned char> value = Utils::DataAsVec(bytebuffer, bufferOccupiedTillVal, valByteSize);
  
  for (int i = 0; i < 4; i++)
    val[i] = valByteSize >> (i * 8);  
  
  val[4] = ' ';

  for (int j = 0; j < valByteSize; j++)
    val[j+5] = value.at(j);


  std::string keystr(key.begin(), key.end());

  logger.LogInfo("Set for " + keystr);
  store->Set(keystr, val);
  
  Utils::WriteResponse(bytebuffer, successResp, connection, bufferSize);
}

void DbServer::Db::GetHandler(int connection, unsigned char* bytebuffer) {
  logger.LogInfo("get cmd recieved");
  
  int keyByteSize = Utils::ReadSizeFromBuf(bytebuffer, commandByteSize + spaceDelimitter);
  int bufferMemoryUsedByMetadata = commandByteSize + spaceDelimitter + sizeof(int) + spaceDelimitter;
  int bufferMemoryToBeUsed = bufferMemoryUsedByMetadata + keyByteSize;

  if (bufferMemoryToBeUsed > bufferSize) {
    Utils::WriteResponse(bytebuffer, bufferSizeContradictionResp, connection, bufferSize);
    return;
  }

  std::vector<unsigned char> key = Utils::DataAsVec(bytebuffer, bufferMemoryUsedByMetadata, keyByteSize);

  std::string keystr(key.begin(), key.end());
  logger.LogInfo("getting " + keystr);

  // result will now contain metadata for valuse size and value as well
  std::vector<unsigned char> result = store->Get(keystr);
  if (result.size() == 0) {
    Utils::WriteResponse(bytebuffer, noVal, connection, bufferSize);
  }
  Utils::WriteVecResponse(bytebuffer, result, connection, bufferSize);
}

void DbServer::Db::DelHandler(int connection, unsigned char* bytebuffer) {
  logger.LogInfo("del cmd recieved");

  int keyByteSize = Utils::ReadSizeFromBuf(bytebuffer, commandByteSize + spaceDelimitter);
  int bufferMemoryUsedByMetadata = commandByteSize + spaceDelimitter + sizeof(int) + spaceDelimitter;
  int bufferMemoryToBeUsed = bufferMemoryUsedByMetadata + keyByteSize;

  if (bufferMemoryToBeUsed > bufferSize) {
    Utils::WriteResponse(bytebuffer, bufferSizeContradictionResp, connection, bufferSize);
    return;
  }
  
  std::vector<unsigned char> key = Utils::DataAsVec(bytebuffer, bufferMemoryUsedByMetadata, keyByteSize);

  std::string keystr(key.begin(), key.end());
  logger.LogInfo("deleting " + keystr);

  store->Del(keystr);

  Utils::WriteResponse(bytebuffer, successResp, connection, bufferSize);
}


void DbServer::Db::AllHandler(int connection, unsigned char* bytebuffer) {
  // the first 4 bytes are reserved for total data packet size;
  std::vector<unsigned char> result(5, 0);
  
  std::vector<std::string> keys = store->AllKeys();
  
  int totalDataSize = 0;

  for (auto key: keys) {
    int keySize = key.size();
    for (int i = 0; i < 4; i++)
      result.push_back(keySize >> (i * 8)); 
    result.push_back(' ');
    for (auto c: key) {
      result.push_back(c);
    }
    result.push_back(' ');
    totalDataSize += 4 + 1 + keySize; // keysize metadata is 4 bytes , 1 is separator, then keySize
  }

  for (int i = 0; i < 4; i++)
    result[i] = totalDataSize >> (i * 8); 
  result[4] = ' ';

  logger.LogInfo("Total Data PacketSize is " + std::to_string(totalDataSize));
  Utils::WriteVecResponse(bytebuffer, result, connection, bufferSize);
}
