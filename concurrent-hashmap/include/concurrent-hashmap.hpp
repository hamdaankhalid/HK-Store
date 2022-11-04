#pragma once

#include <unordered_map>
#include <string>
#include <mutex>
#include<vector>
#include <cstddef>


namespace ConcurMap {

  class MapStore {
    public:
    ~MapStore(){};

    virtual void Set(const std::string& key, const std::vector<unsigned char>& val) = 0;
    virtual std::vector<unsigned char> Get(const std::string& key) = 0;
    virtual void Del(const std::string& key) = 0;
    virtual std::unordered_map<std::string, std::vector<unsigned char>> GetState() = 0;
  };

  class ConcurrentHashmap : public MapStore {
    public:
    void Set(const std::string& key, const std::vector<unsigned char>& val);
    std::vector<unsigned char> Get(const std::string& key);
    void Del(const std::string& key);
    std::unordered_map<std::string, std::vector<unsigned char>> GetState();

    private:
    // key being a string lets us not implement a comparison operation
    std::unordered_map<std::string, std::vector<unsigned char>> map;
    std::mutex mu;
  };
};
