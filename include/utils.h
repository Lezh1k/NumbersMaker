#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
class QFont;
class QString;

int sqrti(int x);
int nearest_square(int x);

int font_max_size(const QFont& font, int shape_w, int shape_h, const QString &str);

#endif // UTILS_H
