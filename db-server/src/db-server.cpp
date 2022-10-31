#include "db-server.hpp"
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <unistd.h> // For read

#define SERVER_PORT 6969


int DbServer::Db::Start(int port) {
  int opt = 1;
  socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socketFd) {
    return -1;
  }

  // Forcefully attaching socket to the port 8080 
  if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
  { 
    return -1;
  }

  struct sockaddr_in sockaddr, cliaddr;
  
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;

  // htons is necessary to convert a number to network byte order
  sockaddr.sin_port = htons(port);
  
  auto bindSuccess = ::bind(socketFd, (struct sockaddr*) &sockaddr, sizeof(sockaddr));

  if (bindSuccess < 0) {
    return -1;
  }

  listenDescriptor = listen(socketFd, 10);
  if (listenDescriptor != 0)
    return -1;
}

// blocking call
int DbServer::Db::Listen() {
  listening = true;

  while (listening) {
    connection = accept(socketFd, (struct sockaddr*) &cliaddr, (socklen_t*)&addrlen);
    if (connection < 0) {
      return -1;
    }
    
    char buffer[4];
    // read buffer and forward to thread that handles?
    recv(connection, buffer, 4, MSG_PEEK);

    // handle each connection and buffer

  }

  return 0;
}

void DbServer::Db::Stop() {
  listening = false;
  close(listenDescriptor);
  shutdown(socketFd, SHUT_RDWR);
}

void DbServer::Db::handleBody(char* buf) {
  
}
