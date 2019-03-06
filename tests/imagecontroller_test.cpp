#include <gtest/gtest.h>
#include "imagecontroller.h"

TEST(imagecontroller, setthumbs) {
  CImageController ic;
  ic.set_thumb_count(1);
  ASSERT_EQ(1, ic.rows());
  ASSERT_EQ(1, ic.cols());

  ic.set_thumb_count(2);
  ASSERT_EQ(2, ic.rows());
  ASSERT_EQ(1, ic.cols());

  ic.set_thumb_count(3);
  ASSERT_EQ(2, ic.rows());
  ASSERT_EQ(2, ic.cols());

  ic.set_thumb_count(4);
  ASSERT_EQ(2, ic.rows());
  ASSERT_EQ(2, ic.cols());

  ic.set_thumb_count(5);
  ASSERT_EQ(3, ic.rows());
  ASSERT_EQ(2, ic.cols());

  ic.set_thumb_count(6);
  ASSERT_EQ(3, ic.rows());
  ASSERT_EQ(2, ic.cols());

  ic.set_thumb_count(7);
  ASSERT_EQ(3, ic.rows());
  ASSERT_EQ(3, ic.cols());

  ic.set_thumb_count(8);
  ASSERT_EQ(3, ic.rows());
  ASSERT_EQ(3, ic.cols());

  ic.set_thumb_count(9);
  ASSERT_EQ(3, ic.rows());
  ASSERT_EQ(3, ic.cols());

  ic.set_thumb_count(10);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(3, ic.cols());

  ic.set_thumb_count(11);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(3, ic.cols());

  ic.set_thumb_count(12);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(3, ic.cols());

  ic.set_thumb_count(13);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(4, ic.cols());

  ic.set_thumb_count(14);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(4, ic.cols());

  ic.set_thumb_count(15);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(4, ic.cols());

  ic.set_thumb_count(16);
  ASSERT_EQ(4, ic.rows());
  ASSERT_EQ(4, ic.cols());

  ic.set_thumb_count(17);
  ASSERT_EQ(5, ic.rows());
  ASSERT_EQ(4, ic.cols());
}
