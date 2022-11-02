#include <gtest/gtest.h>
#include <db-server.hpp>


TEST(DbServerUtils, ReadSizeFromBuf) {
  unsigned char buffer[7];

  int val = 1738;

  buffer[0] = 'x';
  buffer[1] = 'y';

  buffer[2] = (val >> 24) & 0xFF;
  buffer[3] = (val >> 16) & 0xFF;
  buffer[4] = (val >> 8) & 0xFF;
  buffer[5] = val & 0xFF;

  buffer[6] = 'y';
  buffer[7] = 'y';

  int res = DbServer::Utils::ReadSizeFromBuf(buffer, 2);

  EXPECT_EQ(res, val);

  val = 20000;

  buffer[0] = 'x';
  buffer[1] = 'y';

  buffer[2] = (val >> 24) & 0xFF;
  buffer[3] = (val >> 16) & 0xFF;
  buffer[4] = (val >> 8) & 0xFF;
  buffer[5] = val & 0xFF;

  buffer[6] = 'y';
  buffer[7] = 'y';

  res = DbServer::Utils::ReadSizeFromBuf(buffer, 2);
  EXPECT_EQ(res, val);
}

TEST(DbServerUtils, ReadCharsFromBuf) {
  unsigned char expected[] = {'l', 'i', 'k', 'e', 'd'};
  unsigned char falseProphetBuffer[] = {'i', ' ', 'l', 'i', 'k', 'e', 'd', ' ', 'u'};

  unsigned char result[5];
  DbServer::Utils::ReadCharsFromBuf(falseProphetBuffer, 2, 5, result);

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(result[i], expected[i]);
  }
}
