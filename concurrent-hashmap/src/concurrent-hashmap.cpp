#include "concurrent-hashmap.hpp"
#include <string>

void ConcurMap::ConcurrentHashmap::Set(std::string& key, std::vector<std::byte> val) {
  std::unique_lock<std::mutex> lock(mu);
  map.at(key) = val;
}

std::vector<std::byte> ConcurMap::ConcurrentHashmap::Get(std::string& key) {
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

void ConcurMap::ConcurrentHashmap::Del(std::string& key) {
  std::unique_lock<std::mutex> lock(mu);
  map.erase(key);
}
