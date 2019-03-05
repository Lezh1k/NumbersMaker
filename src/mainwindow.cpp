#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDoubleSpinBox>
#include "imagecontroller.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  m_x(0.0),
  m_y(0.0),
  m_txt("TXT") {

  ui->setupUi(this);  
  ui->lbl_image->setScaledContents(false);
  ui->le_text->setText(m_txt);
  m_font = ui->cb_fonts->currentFont();
  m_font.setPointSize(200); //default value in designer

  connect(ui->btn_process, &QPushButton::released, this, &MainWindow::btn_process_released);
  connect(ui->btn_background, &QPushButton::released, this, &MainWindow::btn_background_released);
  connect(ui->btn_output, &QPushButton::released, this, &MainWindow::btn_out_released);

  connect(ui->dsb_x, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb_x_value_changed);
  connect(ui->dsb_y, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &MainWindow::dsb_y_value_changed);
  connect(ui->sb_size, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::sb_size_value_changed);

  connect(ui->le_text, &QLineEdit::textChanged, this, &MainWindow::le_text_text_changed);
  connect(ui->cb_fonts, &QFontComboBox::currentFontChanged, this, &MainWindow::cb_fonts_current_font_changed);
  connect(ui->chk_bold, &QCheckBox::stateChanged, this, &MainWindow::chk_bold_changed);
  connect(ui->chk_italic, &QCheckBox::stateChanged, this, &MainWindow::chk_italic_changed);

  QImage img("/home/lezh1k/NumberMaker/base.jpg");
  img = img.scaled(FRAME_WIDTH, FRAME_HEIGHT);
  m_ic.load_base(img);
}

MainWindow::~MainWindow() {
  delete ui;
}
///////////////////////////////////////////////////////

void MainWindow::btn_process_released() {
  //todo implement generation mechanism
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
  img = img.scaled(FRAME_WIDTH, FRAME_HEIGHT);
  m_ic.load_base(img);
  drawText();
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
  m_x = v;
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::dsb_y_value_changed(double v) {
  m_y = v;
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::le_text_text_changed(const QString &str) {
  m_txt = str;
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::cb_fonts_current_font_changed(const QFont &f) {
  m_font = f;
  m_font.setPointSize(ui->sb_size->value());
  m_font.setItalic(ui->chk_italic->checkState()==Qt::Checked);
  m_font.setBold(ui->chk_bold->checkState()==Qt::Checked);
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::chk_bold_changed(int state) {
  m_font.setBold(state == Qt::Checked);
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::chk_italic_changed(int state) {
  m_font.setItalic(state == Qt::Checked);
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::sb_size_value_changed(int size) {
  m_font.setPointSize(size);
  drawText();
}
///////////////////////////////////////////////////////

void MainWindow::drawText() {
  m_ic.draw_text(m_x, m_y, m_font, Qt::black, m_txt);
  ui->lbl_image->setPixmap(m_ic.compozite_pixmap());
}
///////////////////////////////////////////////////////
