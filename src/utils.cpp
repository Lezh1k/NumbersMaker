#include "utils.h"

int sqrti(int x) {
  // Base cases
  if (x == 0 || x == 1)
    return x;

  // Do Binary Search for floor(sqrt(x))
  int l = 1, r = x, ans = 0;
  int m;
  while (l <= r) {
    m = (l + r) >> 1;
    // If x is a perfect square
    if (m*m == x)
      return m;

    if (m*m < x) {
      l = m + 1;
      ans = m;
      continue;
    }
    //else
    r = m-1;
  }
  return ans;
}
///////////////////////////////////////////////////////

int nearest_square(int x) {
  int val = sqrti(x);
  if (val*val == x) return x;
  val += 1;
  return val*val;
}
///////////////////////////////////////////////////////
