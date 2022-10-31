#include <gtest/gtest.h>
#include <concurrent-hashmap.hpp>


TEST(ConcurrentHashmap, Set) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::string val = "{\"bar\": \"mar\"}";
  EXPECT_NO_THROW(hm.Set(key, val.c_str()));
}

TEST(ConcurrentHashmap, GetASetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::string val = "{\"bar\": \"mar\"}";
  hm.Set(key, val.c_str());
  auto res = hm.Get(key);
  EXPECT_EQ(res, val.c_str());
}

TEST(ConcurrentHashmap, GetAnEmptyVecIfNoSetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  auto res = hm.Get(key);
  EXPECT_EQ(res, "");
}

TEST(ConcurrentHashmap, DelASetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  std::string val = "{\"bar\": \"mar\"}";
  hm.Set(key, val.c_str());
  
  hm.Del(key);
  auto res = hm.Get(key);

  EXPECT_EQ(res, "");
}

TEST(ConcurrentHashmap, DelNonSetValue) {
  ConcurMap::ConcurrentHashmap hm;
  std::string key = "foo";
  
  EXPECT_NO_THROW(hm.Del(key));
}
