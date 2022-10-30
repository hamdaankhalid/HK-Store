#include "db-server.hpp"

#define SERVER_PORT 6969

int DbServer::Db::Start() {
  int opt = 1;
  int socketFd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (-1 == socketFd) {
    perror("server");
    exit(EXIT_FAILURE);
  }
  // Forcefully attaching socket to the port 8080 
  if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) 
  { 
    perror("setsockopt"); 
    exit(EXIT_FAILURE); 
  }

  struct sockaddr_in sockaddr, cliaddr;
  
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;

  // htons is necessary to convert a number to network byte order
  sockaddr.sin_port = htons(SERVER_PORT);
  
  auto bindSuccess = ::bind(socketFd, (struct sockaddr*) &sockaddr, sizeof(sockaddr));

  if (bindSuccess < 0) {
    perror("bind failed"); 
    exit(EXIT_FAILURE);
  }

  int listenDescriptor = listen(socketFd, 10);
  if (listenDescriptor != 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  auto addrlen = sizeof(cliaddr);
  int connection;
  std::cout << "Server started on port " << SERVER_PORT << std::endl;
}

void DbServer::Db::Listen() {
  while (true) {
    connection = accept(socketFd, (struct sockaddr*) &cliaddr, (socklen_t*)&addrlen);
    if (connection < 0) {
      perror("connection accept"); 
      exit(EXIT_FAILURE);
    }
    
    char buffer[4];
    memset(buffer, '\0', 4);
    google::protobuf::uint32 size;
    recv(connection, buffer, 4, MSG_PEEK);
    size = readHdr((char *) buffer);
    handleBody(connection, size, lruc);
  }
}

void DbServer::Db::Stop() {
  close(listenDescriptor);
  shutdown(socketFd, SHUT_RDWR);
}
