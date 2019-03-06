#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDebug>
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#if 0
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
#endif

  MainWindow w;
  w.show();
  return a.exec();
}
