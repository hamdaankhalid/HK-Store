#pragma once

#include<concurrent-hashmap.hpp>

namespace DbServer {
  

  class Db {
    public:
    int Start(int port);
    int Listen();
    void Stop();

    private:
    int socketFd;
    int connection;
    unsigned long addrlen;
    sockaddr_in cliaddr;
    int listenDescriptor;
    bool listening;
    ConcurMap::ConcurrentHashmap store;

    void handleBody(char* buf);
  };
};
