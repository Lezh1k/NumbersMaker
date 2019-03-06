#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagecontroller.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void btn_process_released();
  void btn_background_released();
  void btn_out_released();

  void dsb_x_value_changed(double v);
  void dsb_y_value_changed(double v);

  void le_text_text_changed(const QString &str);
  void cb_fonts_current_font_changed(const QFont &f);

  void chk_bold_changed(int state);
  void chk_italic_changed(int state);

  void sb_size_value_changed(int size);

private:
  static const int FRAME_WIDTH = 800;
  static const int FRAME_HEIGHT = 600;

  Ui::MainWindow *ui;
  QPixmap m_pm_base;
  QPixmap m_pm_text;
  QPixmap m_pm_composite;
  CImageController m_ic;
  void drawText();
};

#endif // MAINWINDOW_H
