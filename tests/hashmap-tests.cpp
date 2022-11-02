#include <gtest/gtest.h>
#include <concurrent-hashmap.hpp>
#include<vector>

TEST(ConcurrentHashmap, Set) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::vector<unsigned char> val = {'f', 'r'};
  EXPECT_NO_THROW(hm.Set(key, val));
}

TEST(ConcurrentHashmap, GetASetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::vector<unsigned char> val = {'f', 'r'};
  hm.Set(key, val);
  auto res = hm.Get(key);
  EXPECT_EQ(res, val);
}

TEST(ConcurrentHashmap, GetAnEmptyVecIfNoSetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::vector<unsigned char> empty = {};
  auto res = hm.Get(key);
  EXPECT_EQ(res, empty);
}

TEST(ConcurrentHashmap, DelASetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::vector<unsigned char> val = {'f', 'r'};
  hm.Set(key, val);
  
  hm.Del(key);
  auto res = hm.Get(key);
  std::vector<unsigned char> empty = {};
  EXPECT_EQ(res, empty);
}

TEST(ConcurrentHashmap, DelNonSetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  
  EXPECT_NO_THROW(hm.Del(key));
}
