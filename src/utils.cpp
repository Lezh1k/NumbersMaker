#include <QFont>
#include <QFontMetrics>
#include <QString>

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

int font_max_size(const QFont &font,
                  int shape_w, int shape_h,
                  const QString &str) {
  QFont tf(font);
  QFontMetrics fm(font);
  int f, l, m;
  l = 4096; f = 0;

  while (f < l) {
    m = (f+l) >> 1;
    tf.setPointSize(m);
    fm = QFontMetrics(tf);

    if (fm.height() > shape_h ||
        fm.width(str) > shape_w) {
      l = m;
    } else {
      f = m+1;
    }
  }
  return l;
}
///////////////////////////////////////////////////////
