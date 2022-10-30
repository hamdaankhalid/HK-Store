#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include<vector>
#include <cstddef>


namespace ConcurMap {
  class ConcurrentHashmap {
    public:
    void Set(std::string& key, std::vector<std::byte> val);
    std::vector<std::byte> Get(std::string& key);
    void Del(std::string& key);

    private:
    std::unordered_map<std::string, std::vector<std::byte>> map;
    std::mutex mu;
  };
};


