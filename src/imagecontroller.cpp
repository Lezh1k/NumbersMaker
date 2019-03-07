#include <QPainter>
#include <math.h>
#include "imagecontroller.h"
#include "utils.h"

CImageController::CImageController() :
  m_rows(1),
  m_cols(1),
  m_thumbs_count(1),
  m_font_size(0.0),
  m_x(0.0),
  m_y(0.0),
  m_txt("TXT"),
  m_color(Qt::black) {
  //do nothing
}
///////////////////////////////////////////////////////

CImageController::CImageController(const QImage &img) :
  m_rows(1),
  m_cols(1),
  m_thumbs_count(1),
  m_font_size(0.0),
  m_x(0.0),
  m_y(0.0),
  m_txt("TXT"),
  m_color(Qt::black) {

  reset(img);
}
///////////////////////////////////////////////////////

CImageController::CImageController(const QString &path) :
  m_rows(1),
  m_cols(1),
  m_thumbs_count(1),
  m_font_size(0.0),
  m_x(0.0),
  m_y(0.0),
  m_txt("TXT"),
  m_color(Qt::black) {

  reset(QImage(path));
}
///////////////////////////////////////////////////////

CImageController::~CImageController() {
}

void CImageController::load_base(const QImage &img) {
  reset(img);
}

void CImageController::load_base(const QString &path) {
  reset(QImage(path));
}
///////////////////////////////////////////////////////

void CImageController::reset(const QImage &img) {
  m_pm_base = QPixmap::fromImage(img);  
  reset_thumb_table();
}
///////////////////////////////////////////////////////

void CImageController::reset_thumb_table() {
  int thumb_w = (m_pm_base.width() - m_cols + 1) / m_cols;
  int thumb_h = (m_pm_base.height() - m_rows + 1) / m_rows;
  m_pm_base_thumb = m_pm_base.scaled(thumb_w, thumb_h);

  m_pm_font_layer = QPixmap(m_pm_base.width(), m_pm_base.height());
  m_pm_font_thumb_layer = QPixmap(m_pm_base_thumb.width(), m_pm_base_thumb.height());

  m_pm_composite = QPixmap(m_pm_base.width()*m_cols, m_pm_base.height()*m_rows); //huge pixmap for result images
  m_pm_composite_thumb = QPixmap(m_pm_base.width(), m_pm_base.height());

  m_pm_font_layer.fill(Qt::transparent);
  m_pm_font_thumb_layer.fill(Qt::transparent);

  m_pm_composite_thumb.fill(Qt::transparent);
}
///////////////////////////////////////////////////////

bool CImageController::make_composite(const QPixmap &src,
                                      QPixmap &font_layer,
                                      QPixmap &composite) {
  QFont tf(m_font);
  int max_size = font_max_size(tf,
                               src.width(),
                               src.height(),
                               m_txt);
  int fs = static_cast<int>(std::floor(max_size*m_font_size));
  tf.setPointSize(fs);

  QPainter p;
  font_layer.fill(Qt::transparent);
  if (!p.begin(&font_layer))
    return false;

  p.setPen(QPen(m_color));
  p.setFont(tf);

  int xi, yi;
  xi = static_cast<int>(std::floor(m_x * src.width()));
  yi = static_cast<int>(std::floor(m_y * src.height()));
  p.drawText(xi, yi, m_txt);
  p.end();

  if (!p.begin(&composite))
    return false;

  int tc = 0;
  for (int ty = 0; ty < m_rows; ++ty) {
    for (int tx = 0; tx < m_cols; ++tx) {
      if (++tc > m_thumbs_count)
        goto thumbs_end;
      int dx = src.width()*tx + tx;
      int dy = src.height()*ty + ty;
      p.drawPixmap(dx, dy, src);
      p.drawPixmap(dx, dy, font_layer);
    }
  }
thumbs_end:

  p.end();
  return true;
}
///////////////////////////////////////////////////////

bool CImageController::draw_thumbs_text() {
  return make_composite(m_pm_base_thumb, m_pm_font_thumb_layer, m_pm_composite_thumb);
}
///////////////////////////////////////////////////////

const QPixmap &CImageController::compozite_thumbs_pixmap() const noexcept {
  return m_pm_composite_thumb;
}
///////////////////////////////////////////////////////

void CImageController::set_thumb_count(int v) noexcept {
  int ns = nearest_square(v);
  m_rows = sqrti(ns);
  m_cols = (v + m_rows - 1) / m_rows;
  m_thumbs_count = v;
}

void CImageController::set_text(const QString &txt) noexcept {
  m_txt = txt;
}
///////////////////////////////////////////////////////

void CImageController::set_text(QString &&txt) noexcept {
  m_txt = txt;
}
///////////////////////////////////////////////////////

//font setters
void CImageController::set_font(const QFont &font) noexcept {
  m_font = font;
}
///////////////////////////////////////////////////////

void CImageController::set_font(QFont &&font) noexcept {
  m_font = font;
}
///////////////////////////////////////////////////////

void CImageController::set_bold(bool is_bold) noexcept {
  m_font.setBold(is_bold);
}
///////////////////////////////////////////////////////

void CImageController::set_italic(bool is_italic) noexcept {
  m_font.setItalic(is_italic);
}
///////////////////////////////////////////////////////

void CImageController::set_font_size(double size) noexcept {
  m_font_size = size;
}
///////////////////////////////////////////////////////
