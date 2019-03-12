#include <assert.h>
#include <QDir>
#include "textcontroller.h"
#include "imagecontroller.h"

CTextController::CTextController(QObject *p) :
  QObject (p),
  m_pic(nullptr) {
}

CTextController::~CTextController() {
  //do nothing
}
///////////////////////////////////////////////////////

bool CTextController::set_numbers_interval(int start,
                                           int end,
                                           int width) {
  if (end < start)
    return false;
  m_lst_texts.clear();
  m_lst_texts.reserve(static_cast<size_t>(end-start));
  while (start <= end)
    m_lst_texts.emplace_back(QString("%1").arg(start++, width, 10, QChar('0')));
  return true;
}
///////////////////////////////////////////////////////

void CTextController::start() {
  int processed = 0;
  do {
    if (!m_pic)
      break;

    int nimg = static_cast<int>(m_lst_texts.size()) / m_pic->thumbs_count();
    std::vector<QString>::const_iterator tif = m_lst_texts.cbegin();
    std::vector<QString>::const_iterator til = m_lst_texts.cend();
    while (nimg--) {
      m_pic->draw_text(tif, til);
      tif += m_pic->thumbs_count();
      QString sp = m_out_dir + QDir::separator() + QString("%1.png").arg(nimg);
      m_pic->compozite_pixmap().save(sp);
      processed += m_pic->thumbs_count();
      emit on_progress(processed, static_cast<int>(m_lst_texts.size()));
    }
  } while (false);
  emit process_finished();
}
///////////////////////////////////////////////////////

void CTextController::interrupt() {
  emit on_interrupt();
  emit process_finished();
}
///////////////////////////////////////////////////////
