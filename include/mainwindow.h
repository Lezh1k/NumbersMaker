#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imagecontroller.h"
#include "textcontroller.h"

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
  void btn_cancel_released();

  void btn_background_released();
  void btn_out_released();

  void dsb_x_value_changed(double v);
  void dsb_y_value_changed(double v);
  void dsb_size_value_changed(double v);
  void sb_thumbs_count_value_changed(int v);

  void le_text_text_changed(const QString &str);
  void cb_fonts_current_font_changed(const QFont &f);

  void chk_bold_changed(int state);
  void chk_italic_changed(int state);

  void on_progress(int current, int total);
  void process_finished();

private:
  static const int FRAME_WIDTH = 600;
  static const int FRAME_HEIGHT = 400;

  Ui::MainWindow *ui;  
  CImageController m_ic;
  CTextController m_tc;
  void draw_thumbs();
};

#endif // MAINWINDOW_H
