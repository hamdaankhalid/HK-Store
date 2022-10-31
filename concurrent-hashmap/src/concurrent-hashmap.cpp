#include "concurrent-hashmap.hpp"
#include <string>
#include <vector>
#include <cstddef>

void ConcurMap::ConcurrentHashmap::Set(std::string& key, const char* val) {
  std::unique_lock<std::mutex> lock(mu);
  map.insert({key, val});
}

const char* ConcurMap::ConcurrentHashmap::Get(std::string& key) {
  std::unique_lock<std::mutex> lock(mu);
  try
  {
   // throws an exception if no key exists
   return map.at(key);
  }
  catch(const std::exception& e)
  {
    return "";
  }
}

void ConcurMap::ConcurrentHashmap::Del(std::string& key) {
  std::unique_lock<std::mutex> lock(mu);
  map.erase(key);
}
