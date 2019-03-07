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
  int m_thumbs_count;

  QPixmap m_pm_base;
  QPixmap m_pm_base_thumb;

  QPixmap m_pm_font_layer;
  QPixmap m_pm_font_thumb_layer;

  QPixmap m_pm_composite;
  QPixmap m_pm_composite_thumb;

  //text settings
  double m_font_size;
  double m_x;
  double m_y;
  QString m_txt;
  QFont m_font;
  QColor m_color;

  bool make_composite(const QPixmap &src,
                      QPixmap &font_layer,
                      QPixmap &composite);
  void reset(const QImage& img);
  void reset_thumb_table();

public:

  CImageController();
  explicit CImageController(const QImage& img);
  explicit CImageController(const QString& path);
  ~CImageController(void);

  void load_base(const QImage& img);
  void load_base(const QString& path);
  bool draw_thumbs_text();


  const QPixmap &compozite_thumbs_pixmap(void) const noexcept;
  //getters and setters
  int rows() const noexcept {return m_rows;}
  int cols() const noexcept {return m_cols;}

  double current_font_size() const noexcept {return m_font_size;}
  double current_x() const noexcept { return m_x;}
  double current_y() const noexcept { return m_y;}
  const QString& current_text() const noexcept {return m_txt;}
  const QFont& current_font() const noexcept {return m_font;}
  const QColor& current_color() const noexcept {return m_color;}

  void set_thumb_count(int v) noexcept;
  void set_x(double x) noexcept { m_x = x;}
  void set_y(double y) noexcept { m_y = y;}

  void set_text(const QString& txt) noexcept;
  void set_text(QString &&txt) noexcept;

  void set_font(const QFont& font) noexcept;
  void set_font(QFont &&font) noexcept;
  void set_bold(bool is_bold) noexcept;
  void set_italic(bool is_italic) noexcept;
  void set_font_size(double size) noexcept;

  void set_color(const QColor& color) noexcept { m_color = color;}
  void set_color(QColor &&color) noexcept {m_color = color;}
  //
};

#endif // IMAGECONTROLLER_H
