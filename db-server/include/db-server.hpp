#pragma once

#include<iostream>
#include<memory>
#include<concurrent-hashmap.hpp>
#include<logger.hpp>

namespace DbServer {
  class Db {
    public:

    Db(int p);

    int Listen();

    ~Db();

    private:

    int port;
    int socketFd;
    int connection;
    unsigned long addrlen;
    sockaddr_in cliaddr;
    int listenDescriptor;
    bool listening;
    CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(std::cout);

    std::shared_ptr<ConcurMap::ConcurrentHashmap> store = std::make_shared<ConcurMap::ConcurrentHashmap>();

    int start();
    void stop();

    void handleBody(char* buf);

    // handlers are pure function but write to buf
    void getHandler();
    void setHandler();
    void delHandler();  

    // buffer to json and json to buffer helpers
    void vecBufToJsn(std::vector<char> buf);
    std::vector<char> jsnVecBuf(std::string rawjsonliteral);
  };
};
