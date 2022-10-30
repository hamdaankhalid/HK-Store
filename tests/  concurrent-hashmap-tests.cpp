#include<gtest/gtest.h>
#include<concurrent_hashmap.hpp>
#include <algorithm>

// namespace Util {
//   std::vector<std::byte> StringToByteVec(const std::string& s) {
//     std::vector<std::byte> byteVec(s.size());
//     std::transform(std::begin(s), std::end(s), std::back_inserter(byteVec), [](char c){
//       return std::byte(c);
//     });
//     return byteVec;
//   }
// }

TEST(ConcurrentHashmap, Set) {
  // ConcurMap::ConcurrentHashmap hm;
  // EXPECT_NO_THROW(hm.Set("foo", StringToByteVec("bar")));
}
