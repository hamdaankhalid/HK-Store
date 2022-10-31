#pragma once

#include<iostream>
#include<memory>
#include<concurrent-hashmap.hpp>
#include<logger.hpp>
#include<unordered_map>

namespace DbServer {
  enum Commands {
    SET,
    GET,
    DEL
  };

  class Db {
    public:

    Db(int p);

    int Listen();

    ~Db();

    private:
    static const int bufferSize = 2000;
    static const int commandByteSize = 3;
    static const std::string unknownCommandResp;
    static const std::string noVal;

    int port;
    int socketFd;
    int connection;
    unsigned long addrlen;
    sockaddr_in cliaddr;
    int listenDescriptor;
    bool listening;
    std::unordered_map<std::string, Commands> cmdMap = {
      {"SET", Commands::SET},
      {"GET", Commands::GET},
      {"DEL", Commands::DEL}
    };

    CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(std::cout);

    std::shared_ptr<ConcurMap::ConcurrentHashmap> store = std::make_shared<ConcurMap::ConcurrentHashmap>();

    int start();
    void stop();

    void handleBody(int connection);
    std::string readCommandHeader(char* bytebuffer);

    // handlers are pure function but write to buf
    void getHandler(int connection, char* bytebuffer);
    void setHandler(int connection, char* bytebuffer);
    void delHandler(int connection, char* bytebuffer);

    // buffer to json and json to buffer helpers
    void vecBufToJsn(std::vector<char> buf);
    std::vector<char> jsnVecBuf(std::string rawjsonliteral);
  };
};
