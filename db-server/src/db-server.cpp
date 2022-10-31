#include "db-server.hpp"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h> // For read
#include <stdexcept>
#include <string>

#define SERVER_PORT 6969

DbServer::Db::Db(int p): port(p) {
  int success = start();
  if (success != 0) {
    logger.LogError("Unable to boot error");
    throw "Unable to boot up server";
  }
}

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
    
    char buffer[4];
    // read buffer and forward to thread that handles?
    recv(connection, buffer, 4, MSG_PEEK);

    // handle each connection and buffer
    // TODO
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

void DbServer::Db::handleBody(char* buf) {
  // TODO
}

void getHandler() {
  // TODO
}

void setHandler() {
  // TODO
}

void delHandler() {
  // TODO
}

void vecBufToJsn(std::vector<char> buf) {
  // TODO
}

std::vector<char> jsnVecBuf(std::string rawjsonliteral) {
  // TODO
}
