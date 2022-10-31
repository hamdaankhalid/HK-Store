#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include<vector>
#include <cstddef>


namespace ConcurMap {
  class ConcurrentHashmap {
    public:
    void Set(std::string& key, const char* val);
    const char* Get(std::string& key);
    void Del(std::string& key);

    private:
    std::unordered_map<std::string, const char*> map;
    std::mutex mu;
  };
};


