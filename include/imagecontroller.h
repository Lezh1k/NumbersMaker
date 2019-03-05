#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QFont>
#include <QColor>

class CImageController : QObject {
  Q_OBJECT

private:
  QPixmap m_pm_base;
  QPixmap m_pm_font_layer;
  QPixmap m_pm_composite;

  void reset(const QImage& img);
public:
  CImageController(QObject *parent = nullptr);
  explicit CImageController(const QImage& img);
  explicit CImageController(const QString& path);
  virtual ~CImageController(void);

  int current_width(void) const noexcept{return m_pm_base.isNull() ? 0 : m_pm_base.width();}
  int current_height(void) const noexcept{return m_pm_base.isNull() ? 0 : m_pm_base.height();}
  const QPixmap &compozite_pixmap(void) const noexcept{ return m_pm_composite; }

  void load_base(const QImage& img);
  void load_base(const QString& path);

  bool draw_text(double x,
                 double y,
                 const QFont &font,
                 const QColor &color,
                 const QString &txt);
};

#endif // IMAGECONTROLLER_H
