#include "concurrent-hashmap.hpp"
#include <string>
#include <vector>
#include <cstddef>

void ConcurMap::ConcurrentHashmap::Set(const std::string& key, const std::vector<unsigned char>& val) {
  std::unique_lock<std::mutex> lock(mu);
  map.insert({key, val});
}

std::vector<unsigned char> ConcurMap::ConcurrentHashmap::Get(const std::string& key) {
  std::unique_lock<std::mutex> lock(mu);
  try
  {
   // throws an exception if no key exists
   return map.at(key);
  }
  catch(const std::exception& e)
  {
    return {};
  }
}

void ConcurMap::ConcurrentHashmap::Del(const std::string& key) {
  std::unique_lock<std::mutex> lock(mu);
  map.erase(key);
}

std::unordered_map<std::string, std::vector<unsigned char>> ConcurMap::ConcurrentHashmap::GetState() {
  return map;
}