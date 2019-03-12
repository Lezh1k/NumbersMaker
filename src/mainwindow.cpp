#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDoubleSpinBox>
#include <QThread>

#include "imagecontroller.h"
#include "textcontroller.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {

  ui->setupUi(this);  
  ui->lbl_image->setScaledContents(false);
  ui->le_text->setText(m_ic.current_text());

  m_tc.set_pic(&m_ic);
  m_ic.set_font(ui->cb_fonts->currentFont());
  static const double initial_size = 0.35;
  ui->dsb_font_size->setValue(initial_size);

  connect(ui->btn_background, &QPushButton::released, this, &MainWindow::btn_background_released);
  connect(ui->btn_output, &QPushButton::released, this, &MainWindow::btn_out_released);

  connect(ui->sb_thubm_count, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::sb_thumbs_count_value_changed);
  connect(ui->dsb_x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb_x_value_changed);
  connect(ui->dsb_y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb_y_value_changed);
  connect(ui->dsb_font_size, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb_size_value_changed);

  connect(ui->le_text, &QLineEdit::textChanged, this, &MainWindow::le_text_text_changed);
  connect(ui->cb_fonts, &QFontComboBox::currentFontChanged, this, &MainWindow::cb_fonts_current_font_changed);
  connect(ui->chk_bold, &QCheckBox::stateChanged, this, &MainWindow::chk_bold_changed);
  connect(ui->chk_italic, &QCheckBox::stateChanged, this, &MainWindow::chk_italic_changed);

  connect(ui->btn_process, &QPushButton::released, this, &MainWindow::btn_process_released);
  connect(ui->btn_cancel, &QPushButton::released, this, &MainWindow::btn_cancel_released);

  connect(&m_tc, &CTextController::on_progress, this, &MainWindow::on_progress);
  connect(&m_tc, &CTextController::process_finished, this, &MainWindow::process_finished);
}

MainWindow::~MainWindow() {
  delete ui;
}
///////////////////////////////////////////////////////

void MainWindow::btn_process_released() {
  QString out_dir = ui->le_output->text();
  if (out_dir.isNull() || out_dir.isEmpty())
    out_dir = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last();
  int width = m_ic.current_text().size();
  if (width <= 0)
    width = 1;

  m_tc.set_out_dir(out_dir);
  int first = ui->sb_first->value();
  int last = ui->sb_last->value();
  if (!m_tc.set_numbers_interval(first, last, width)) {
    //todo show error msg;
    return;
  }

  ui->btn_cancel->setEnabled(true);
  ui->btn_process->setEnabled(false);
  QThread *th = new QThread;
  connect(th, &QThread::started, &m_tc, &CTextController::start);
  connect(&m_tc, &CTextController::process_finished, th, &QThread::quit);
  connect(th, &QThread::finished, th, &QThread::deleteLater);

  th->start();
}

void MainWindow::btn_cancel_released() {
  m_tc.interrupt();
  ui->btn_cancel->setEnabled(false);
  ui->btn_process->setEnabled(true);
}
///////////////////////////////////////////////////////

void MainWindow::btn_background_released() {
  QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last();
  QString img_path = QFileDialog::getOpenFileName(this, tr("Open Image"),
                                                  home, tr("Image Files (*.png *.jpg *.bmp)"));
  if (img_path.isNull() || img_path.isEmpty())
    return;
  ui->le_base->setText(img_path);
  QImage img(img_path);
  img = img.scaled(ui->lbl_image->width(), ui->lbl_image->height());
  m_ic.load_base(img);
  m_ic.set_font_size(ui->dsb_font_size->value());
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::btn_out_released() {
  QString home = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).last();
  QString dir = QFileDialog::getExistingDirectory(this, tr("Generate numbers folder"), home);
  if (dir.isNull() || dir.isEmpty())
    return;
  ui->le_output->setText(dir);
}
///////////////////////////////////////////////////////

void MainWindow::dsb_x_value_changed(double v) {
  m_ic.set_x(v);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::dsb_y_value_changed(double v) {
  m_ic.set_y(v);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::le_text_text_changed(const QString &str) {
  m_ic.set_text(str);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::cb_fonts_current_font_changed(const QFont &f) {
  m_ic.set_font(f);
  m_ic.set_font_size(ui->dsb_font_size->value());
  m_ic.set_italic(ui->chk_italic->checkState() == Qt::Checked);
  m_ic.set_bold(ui->chk_bold->checkState() == Qt::Checked);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::chk_bold_changed(int state) {
  m_ic.set_bold(state == Qt::Checked);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::chk_italic_changed(int state) {
  m_ic.set_italic(state == Qt::Checked);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::on_progress(int current, int total) {
  ui->pb_progress->setMaximum(total);
  ui->pb_progress->setValue(current);
}
///////////////////////////////////////////////////////

void MainWindow::process_finished() {
  ui->btn_cancel->setEnabled(false);
  ui->btn_process->setEnabled(true);
}
///////////////////////////////////////////////////////

void MainWindow::dsb_size_value_changed(double v) {
  m_ic.set_font_size(v);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::sb_thumbs_count_value_changed(int v) {
  m_ic.set_thumb_count(v);
  draw_thumbs();
}
///////////////////////////////////////////////////////

void MainWindow::draw_thumbs() {
  m_ic.draw_thumbs_text();
  ui->lbl_image->setPixmap(m_ic.compozite_thumbs_pixmap());
}
///////////////////////////////////////////////////////
