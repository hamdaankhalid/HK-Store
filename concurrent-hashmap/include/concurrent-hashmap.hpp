#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include<vector>
#include <cstddef>


namespace ConcurMap {
  class ConcurrentHashmap {
    public:
    void Set(const std::string& key, const char* val);
    const char* Get(const std::string& key);
    void Del(const std::string& key);

    private:
    // key being a string lets us not implement a comparison operation
    std::unordered_map<std::string, char*> map;
    std::mutex mu;
  };
};
