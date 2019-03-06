#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <QObject>
#include <QImage>
#include <QPixmap>
#include <QFont>
#include <QColor>

class CImageController {

private:  
  int m_rows;
  int m_cols;
  //image settings
  QPixmap m_pm_base;
  QPixmap m_pm_base_thumb;
  QPixmap m_pm_font_layer;
  QPixmap m_pm_composite;

  //text settings
  double m_x;
  double m_y;
  QString m_txt;
  QFont m_font;
  QColor m_color;

  void reset(const QImage& img);
  void reset_thumb_table();

public:

  CImageController();
  explicit CImageController(const QImage& img);
  explicit CImageController(const QString& path);
  ~CImageController(void);

  void load_base(const QImage& img);
  void load_base(const QString& path);
  bool draw_text();

  int current_width(void) const noexcept;
  int current_height(void) const noexcept;
  const QPixmap &compozite_pixmap(void) const noexcept;
  //getters and setters

  int rows() const noexcept {return m_rows;}
  int cols() const noexcept {return m_cols;}

  double current_x() const noexcept { return m_x;}
  double current_y() const noexcept { return m_y;}
  const QString& current_text() const noexcept {return m_txt;}
  const QFont& current_font() const noexcept {return m_font;}
  const QColor& current_color() const noexcept {return m_color;}

  void set_thumb_count(int v) noexcept;

  void set_x(double x) noexcept { m_x = x;}
  void set_y(double y) noexcept { m_y = y;}

  void set_text(const QString& txt) noexcept { m_txt = txt;}
  void set_text(QString &&txt) { m_txt = txt;}

  void set_font(const QFont& font) noexcept { m_font = font;}
  void set_font(QFont &&font) noexcept {m_font = font;}

  void set_bold(bool is_bold) noexcept { m_font.setBold(is_bold);}
  void set_italic(bool is_italic) noexcept { m_font.setItalic(is_italic);}

  //todo CHECK! seems that it's mistake in qfont documentation.
  void set_font_size(int size) noexcept {
//    m_font.setPointSize(size);
    m_font.setPixelSize(size);
  }

  void set_color(const QColor& color) noexcept { m_color = color;}
  void set_color(QColor &&color) noexcept {m_color = color;}
  //
};

#endif // IMAGECONTROLLER_H
