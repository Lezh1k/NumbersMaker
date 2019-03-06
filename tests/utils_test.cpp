#include <gtest/gtest.h>
#include "utils.h"

TEST(utils, sqrti) {
  ASSERT_EQ(1, sqrti(1));
  ASSERT_EQ(1, sqrti(2));
  ASSERT_EQ(1, sqrti(3));

  ASSERT_EQ(2, sqrti(4));
  ASSERT_EQ(2, sqrti(5));
  ASSERT_EQ(2, sqrti(6));
  ASSERT_EQ(2, sqrti(7));
  ASSERT_EQ(2, sqrti(8));

  ASSERT_EQ(3, sqrti(9));
  ASSERT_EQ(3, sqrti(10));
}
///////////////////////////////////////////////////////

TEST(utils, nearest_square) {
  ASSERT_EQ(1, nearest_square(1));
  ASSERT_EQ(4, nearest_square(3));
  ASSERT_EQ(4, nearest_square(4));
  ASSERT_EQ(9, nearest_square(5));
  ASSERT_EQ(9, nearest_square(6));
  ASSERT_EQ(9, nearest_square(9));
}
