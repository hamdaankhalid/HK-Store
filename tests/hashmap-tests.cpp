#include <gtest/gtest.h>
#include <concurrent-hashmap.hpp>

namespace Util {
  std::vector<std::byte> StringToByteVec(const std::string& s) {
    std::vector<std::byte> byteVec(s.size());
    std::transform(std::begin(s), std::end(s), std::back_inserter(byteVec), [](char c){
      return std::byte(c);
    });
    return byteVec;
  }
}

TEST(ConcurrentHashmap, Set) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::string val = "{\"bar\": \"mar\"}";
  auto v = Util::StringToByteVec(val);
  EXPECT_NO_THROW(hm.Set(key, v));
}

TEST(ConcurrentHashmap, GetASetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::string val = "{\"bar\": \"mar\"}";
  auto bytevec = Util::StringToByteVec(val);
  hm.Set(key, bytevec);
  auto res = hm.Get(key);
  EXPECT_EQ(res, bytevec);
}

TEST(ConcurrentHashmap, GetAnEmptyVecIfNoSetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  auto res = hm.Get(key);
  std::vector<std::byte> empty;
  EXPECT_EQ(res, empty);
}

TEST(ConcurrentHashmap, DelASetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::string val = "{\"bar\": \"mar\"}";
  auto bytevec = Util::StringToByteVec(val);
  hm.Set(key, bytevec);
  
  hm.Del(key);
  auto res = hm.Get(key);

  std::vector<std::byte> empty;
  EXPECT_EQ(res, empty);
}

TEST(ConcurrentHashmap, DelNonSetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  
  EXPECT_NO_THROW(hm.Del(key));
}
