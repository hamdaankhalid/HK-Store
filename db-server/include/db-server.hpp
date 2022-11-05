#pragma once

#include <iostream>
#include <memory>
#include <concurrent-hashmap.hpp>
#include <logger.hpp>
#include <unordered_map>
#include <netinet/in.h> // For sockaddr_in


namespace DbServer {

  namespace Utils {
    std::vector<unsigned char> DataAsVec(unsigned char* byteBuffer, int startPosition, int size);
    int ReadSizeFromBuf(unsigned char* byteBuffer, int offset);
    void WriteResponse(unsigned char* byteBuffer, const std::string& response, int connection, int bufferSize);
    void WriteVecResponse(unsigned char* byteBuffer, const std::vector<unsigned char> response, int connection, int bufferSize);
  }

  enum Commands {
    SET,
    GET,
    DEL,
    NEG
  };

  class Db {
    public:

    Db(std::shared_ptr<ConcurMap::MapStore> storage, int p);

    int Listen();

    ~Db();

    private:
    static const int bufferSize = 2000;
    static const int commandByteSize = 3;
    static const int spaceDelimitter = 1;
    
    static const std::string unknownCommandResp;
    static const std::string bufferSizeContradictionResp;
    static const std::string successResp;

    static const std::string noVal;
    
    static const std::unordered_map<std::string, Commands> cmdMap;

    int port;
    int socketFd;
    int connection;
    unsigned long addrlen;
    sockaddr_in cliaddr;
    int listenDescriptor;
    bool listening;
    

    CustomLogger::Logger& logger = CustomLogger::Logger::GetInstance(std::cout);

    std::shared_ptr<ConcurMap::MapStore> store;

    int Start();
    void Stop();

    void HandleBody(int connection);
    Commands ReadCommandHeader(unsigned char* bytebuffer);

    // handlers are pure function but write to buf
    void GetHandler(int connection, unsigned char* bytebuffer);
    void SetHandler(int connection, unsigned char* bytebuffer);
    void DelHandler(int connection, unsigned char* bytebuffer);
  };
};
