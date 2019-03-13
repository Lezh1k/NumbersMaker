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
  m_txt("28"),
  m_color(Qt::black) {
}
///////////////////////////////////////////////////////

CImageController::~CImageController() {
}

void CImageController::load_base(const QImage &img, int w, int h) {
  reset(img, w, h);
}

void CImageController::load_base(const QString &path, int w, int h) {
  reset(QImage(path), w, h);
}
///////////////////////////////////////////////////////

void CImageController::reset(const QImage &img, int w, int h) {
  m_pm_base = QPixmap::fromImage(img);  
  m_scaled_base_h = h;
  m_scaled_base_w = w;
  reset_thumb_table();
}
///////////////////////////////////////////////////////

void CImageController::reset_thumb_table() {
  int thumb_w = m_scaled_base_w / m_cols - 1;
  int thumb_h = m_scaled_base_h / m_rows - 1;

  m_pm_base_thumb = m_pm_base.scaled(thumb_w, thumb_h, Qt::KeepAspectRatio);
  m_pm_font_layer = QPixmap(m_pm_base.width(), m_pm_base.height());
  m_pm_font_layer_thumb = QPixmap(m_pm_base_thumb.width(), m_pm_base_thumb.height());

  m_pm_composite = QPixmap(m_pm_base.width()*m_cols, m_pm_base.height()*m_rows); //huge pixmap for result images. WARNING!
  m_pm_composite_thumb = QPixmap(m_scaled_base_w, m_scaled_base_h);

  m_pm_font_layer.fill(Qt::transparent);
  m_pm_font_layer_thumb.fill(Qt::transparent);

  m_pm_composite.fill(Qt::black);
  m_pm_composite_thumb.fill(Qt::transparent);
}
///////////////////////////////////////////////////////

bool CImageController::draw_text(std::vector<QString>::const_iterator tif,
                                 std::vector<QString>::const_iterator til) {
  QFont tf(m_font);
  int max_size = font_max_size(tf,
                               m_pm_base.width(),
                               m_pm_base.height(),
                               m_txt);
  int fs = static_cast<int>(std::floor(max_size*m_font_size));
  tf.setPointSize(fs);

  QPainter p;
  int xi, yi;
  xi = static_cast<int>(std::floor(m_x * m_pm_base.width()));
  yi = static_cast<int>(std::floor(m_y * m_pm_base.height()));

  int tc = 0;
  for (int ty = 0; ty < m_rows; ++ty) {
    for (int tx = 0; tx < m_cols; ++tx) {
      m_pm_font_layer.fill(Qt::transparent);
      if (!p.begin(&m_pm_font_layer))
        return false;

      p.setPen(QPen(m_color));
      p.setFont(tf);
      p.drawText(xi, yi, *tif);
      p.end();

      if (!p.begin(&m_pm_composite))
        return false;

      int dx = m_pm_base.width()*tx + tx;
      int dy = m_pm_base.height()*ty + ty;
      p.drawPixmap(dx, dy, m_pm_base);
      p.drawPixmap(dx, dy, m_pm_font_layer);
      p.end();

      if (++tc > m_thumbs_count || ++tif == til)
        goto end;
    }
  }
end:

  return true;
}
///////////////////////////////////////////////////////

bool CImageController::draw_thumbs_text() {
  QFont tf(m_font);
  int max_size = font_max_size(tf,
                               m_pm_base_thumb.width(),
                               m_pm_base_thumb.height(),
                               m_txt);
  int fs = static_cast<int>(std::floor(max_size*m_font_size));
  tf.setPointSize(fs);

  QPainter p;
  m_pm_font_layer_thumb.fill(Qt::transparent);
  if (!p.begin(&m_pm_font_layer_thumb))
    return false;

  p.setPen(QPen(m_color));
  p.setFont(tf);

  int xi, yi;
  xi = static_cast<int>(std::floor(m_x * m_pm_base_thumb.width()));
  yi = static_cast<int>(std::floor(m_y * m_pm_base_thumb.height()));
  p.drawText(xi, yi, m_txt);
  p.end();

  if (!p.begin(&m_pm_composite_thumb))
    return false;

  int tc = 0;
  for (int tx = 0; tx < m_cols; ++tx) {
    for (int ty = 0; ty < m_rows; ++ty) {
      if (++tc > m_thumbs_count)
        goto thumbs_end;
      int dx = m_pm_base_thumb.width()*tx + tx;
      int dy = m_pm_base_thumb.height()*ty + ty;
      p.drawPixmap(dx, dy, m_pm_base_thumb);
      p.drawPixmap(dx, dy, m_pm_font_layer_thumb);
    }
  }
thumbs_end:

  p.end();
  return true;
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
  reset_thumb_table();
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
