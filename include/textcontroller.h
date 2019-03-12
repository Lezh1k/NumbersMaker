#ifndef TEXTCONTROLLER_H
#define TEXTCONTROLLER_H

#include <vector>
#include <QString>
#include <QObject>
class CImageController;

class CTextController : public QObject {
  Q_OBJECT
private:
  QString m_out_dir;
  std::vector<QString> m_lst_texts;
  CImageController *m_pic;

public:
  CTextController(QObject *p = nullptr);
  virtual ~CTextController();

  void set_pic(CImageController* pic) {m_pic = pic;}
  void set_out_dir(const QString& out_dir) {m_out_dir = out_dir;}
  bool set_numbers_interval(int start, int end, int width);
  void interrupt();

public slots:
  void start();

signals:
  void on_interrupt();
  void on_progress(int current, int total);
  void process_finished();
};

#endif // TEXTCONTROLLER_H
