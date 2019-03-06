#include <QPainter>
#include <math.h>
#include "imagecontroller.h"
#include "utils.h"

CImageController::CImageController() :
  m_rows(1),
  m_cols(1),
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
  m_rows = 2;
  m_cols = 2;
  reset_thumb_table();
}
///////////////////////////////////////////////////////

void CImageController::reset_thumb_table() {
  int thumb_w = (m_pm_base.width() - m_cols + 1) / m_cols;
  int thumb_h = (m_pm_base.height() - m_rows + 1) / m_rows;
  m_pm_base_thumb = m_pm_base.scaled(thumb_w, thumb_h);
  m_pm_font_layer = QPixmap(m_pm_base_thumb.width(), m_pm_base_thumb.height());

  m_pm_composite = QPixmap(m_pm_base.width(), m_pm_base.height());
  m_pm_font_layer.fill(Qt::transparent);
  m_pm_composite.fill(Qt::transparent);
}
///////////////////////////////////////////////////////

bool CImageController::draw_text() {
  QPainter p;
  m_pm_font_layer.fill(Qt::transparent);
  if (!p.begin(&m_pm_font_layer))
    return false;

  p.setPen(QPen(m_color));
  p.setFont(m_font);

  int xi, yi;
  xi = static_cast<int>(std::floor(m_x * m_pm_base_thumb.width()));
  yi = static_cast<int>(std::floor(m_y * m_pm_base_thumb.height()));
  p.drawText(xi, yi, m_txt);
  p.end();

  if (!p.begin(&m_pm_composite))
    return false;

  //warning!
  for (int ty = 0; ty < m_rows; ++ty) {
    for (int tx = 0; tx < m_cols; ++tx) {
      int dx = m_pm_base_thumb.width()*tx + tx;
      int dy = m_pm_base_thumb.height()*ty + ty;
      p.drawPixmap(dx, dy, m_pm_base_thumb);
      p.drawPixmap(dx, dy, m_pm_font_layer);
    }
  }

  p.end();
  return true;
}
///////////////////////////////////////////////////////

int CImageController::current_width() const noexcept {
  return m_pm_base.isNull() ? 0 : m_pm_base.width();
}
///////////////////////////////////////////////////////

int CImageController::current_height() const noexcept {
  return m_pm_base.isNull() ? 0 : m_pm_base.height();
}
///////////////////////////////////////////////////////

const QPixmap &CImageController::compozite_pixmap() const noexcept {
  return m_pm_composite;
}
///////////////////////////////////////////////////////

void CImageController::set_thumb_count(int v) noexcept {
  int ns = nearest_square(v);
  m_rows = sqrti(ns);
  m_cols = (v + m_rows - 1) / m_rows;

}
///////////////////////////////////////////////////////
