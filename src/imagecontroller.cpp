#include <QPainter>
#include <math.h>
#include "imagecontroller.h"

CImageController::CImageController(QObject *parent) : QObject(parent) {
}
///////////////////////////////////////////////////////

CImageController::CImageController(const QImage &img) {
  reset(img);
}
///////////////////////////////////////////////////////

CImageController::CImageController(const QString &path) {
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
  m_pm_font_layer = QPixmap(m_pm_base.width(), m_pm_base.height());
  m_pm_composite = QPixmap(m_pm_base.width(), m_pm_base.height());
  m_pm_font_layer.fill(Qt::transparent);
  m_pm_composite.fill(Qt::transparent);
}
///////////////////////////////////////////////////////

bool CImageController::draw_text(double x,
                                 double y,
                                 const QFont &font,
                                 const QColor &color,
                                 const QString &txt) {

  QPainter p;
  m_pm_font_layer.fill(Qt::transparent);
  if (!p.begin(&m_pm_font_layer))
    return false;

  p.setPen(QPen(color));
  p.setFont(font);
  int xi, yi;
  xi = static_cast<int>(std::floor(x * m_pm_base.width()));
  yi = static_cast<int>(std::floor(y * m_pm_base.height()));
  p.drawText(xi, yi, txt);
  p.end();

  if (!p.begin(&m_pm_composite))
    return false;

  p.drawPixmap(0, 0, m_pm_base);
  p.drawPixmap(0, 0, m_pm_font_layer);
  p.end();
  return true;
}
///////////////////////////////////////////////////////
