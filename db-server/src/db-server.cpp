#include "db-server.hpp"

#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h> // For read


#include <stdexcept>
#include <string>
#include<thread>
#include <cstring>

#define SERVER_PORT 6969


int readSizeFromBuf(char* byteBuffer, int offset) {
  int value;
  std::copy(byteBuffer+offset, byteBuffer+offset+sizeof(int), reinterpret_cast<char*>(value));
  return value;
}

// Note: before invoking this function we perform  validation against potential buffer overflow
char* readCharsFromBuf(char* byteBuffer, int startPosition, int size) {
  char[size]  result;
  std::copy(byteBuffer+startPosition, byteBuffer+startPosition+size, result);
  return result;
}

void writeResponse(char* byteBuffer, const std::string& response, int connection) {
  std::memset(bytebuffer, 0, bufferSize);
  memcpy(bytebuffer, response.c_str(), response.size());
  write(connection, bytebuffer, bufferSize);
}

DbServer::Db::Db(int p): port(p) {
  int success = start();
  if (success != 0) {
    logger.LogError("Unable to boot error");
    throw "Unable to boot up server";
  }
}

const std::string DbServer::Db::bufferSizeContradictionResp = "size contradiction\n";

const std::string DbServer::Db::unknownCommandResp = "Another one\n";

const std::string DbServer::Db::successResp = "success\n";

const std::string DbServer::Db::noVal = "";

const std::unordered_map<std::string, DbServer::Commands> DbServer::Db::cmdMap = {
  {"SET", Commands::SET},
  {"GET", Commands::GET},
  {"DEL", Commands::DEL}
};

// blocking call
int DbServer::Db::Listen() {
  
  listening = true;

  logger.LogInfo("Server listening and accepting connections on port " + std::to_string(port));

  while (listening) {
    connection = accept(socketFd, (struct sockaddr*) &cliaddr, (socklen_t*)&addrlen);
    if (connection < 0) {
      logger.LogError("Error accepting connection");
      return -1;
    }

    // handle each connection by passing the buffer down to a thread
    std::thread requesthandlerthread([&]() -> void {
      logger.LogInfo("Connection recieved!");
      handleBody(connection);
    });
    requesthandlerthread.detach();
  }

  return 0;
}

DbServer::Db::~Db(){
  stop();
}

int DbServer::Db::start() {
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

void DbServer::Db::stop() {
  logger.LogInfo("Stopping db server");
  listening = false;
  close(listenDescriptor);
  shutdown(socketFd, SHUT_RDWR);
}

void DbServer::Db::handleBody(int connection) {
  char bytebuffer[bufferSize];
  
  read(connection, bytebuffer, bufferSize);
  
  auto cmd = readCommandHeader(bytebuffer);

  switch (cmd) {
    case Commands::SET:
      setHandler(connection, bytebuffer);
      break;
    case Commands::GET:
      getHandler(connection, bytebuffer);
      break;
    case Commands::DEL:
      delHandler(connection, bytebuffer);
      break;
    default:
      logger.LogError("Command not found");
      writeResponse(bytebuffer, unknownCommandResp, connection);
      break;
  }
  // after we write back a response we can close our connection cutely
  close(connection);
}

DbServer::Commands DbServer::Db::readCommandHeader(char* bytebuffer) {
  char cmdreaderbuf[commandByteSize];
  memcpy(cmdreaderbuf, bytebuffer, commandByteSize);

  std::string commandstr(cmdreaderbuf);
  logger.LogInfo("command decoded from buffer: "commandstr);
  
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
void DbServer::Db::setHandler(int connection, char* bytebuffer) {
  // from bytebuffer contains key and value
  logger.LogInfo("set cmd recieved");

  // we are going to strictly deal with int32 4 bytes in buffer sent 
  // first n bytes (commandByteSize) are taken over to signify command.
  int keyByteSize = readSizeFromBuf(bytebuffer, commandByteSize + spaceDelimitter);
  int valByteSize = readSizeFromBuf(bytebuffer, commandByteSize + spaceDelimitter + sizeof(int) + spaceDelimitter);

  // CMD_KEYSIZEBYTES_VALSIZEBYTES_KEY..._VAL...
  int bufferMemoryUsedByMetadata = commandByteSize + spaceDelimitter + sizeof(int) + spaceDelimitter + sizeof(int);
  int bufferMemoryToBeUsed = keyByteSize+valByteSize+bufferMemoryUsedByMetadata+spaceDelimitter;

  if (bufferMemoryToBeUsed > bufferSize) {
    writeResponse(bytebuffer, bufferSizeContradictionResp, connection);
    return;
  }

  int bufferOccupiedTillKeyIdx = bufferMemoryUsedByMetadata;
  char* key = readCharsFromBuf(byteBuffer, bufferOccupiedTillKeyIdx, keySize);
  
  bufferOccupiedTillValIdx = bufferOccupiedTillKeyIdx+spaceDelimitter;
  char* val = readCharsFromBuf(byteBuffer, bufferOccupiedTillValIdx, valSize);

  std::string keystr(key);
  cmdMap.Get(keystr, val);

  writeResponse(bytebuffer, successResp, connection);
}

void DbServer::Db::getHandler(int connection, char* bytebuffer) {
  // TODO
  logger.LogInfo("get cmd recieved");
  writeResponse(bytebuffer, successResp, connection);
}

void DbServer::Db::delHandler(int connection, char* bytebuffer) {
  // TODO
  logger.LogInfo("del cmd recieved");
  writeResponse(bytebuffer, successResp, connection);
}

void DbServer::Db::vecBufToJsn(std::vector<char> buf) {
  // TODO
}

std::vector<char> DbServer::Db::jsnVecBuf(std::string rawjsonliteral) {
  // TODO
  return {};
}
