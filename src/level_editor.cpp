#include "level_editor.h"

#include <QKeyEvent>
#include <QApplication>

namespace bigmama
{

LevelEditor::LevelEditor(QWidget *parent)
    : QMainWindow(parent), 
    m_centralWidget(), m_frame(), m_board(nullptr), 
    m_assetChooser(), m_layout()
{
  setCentralWidget(&m_centralWidget);  

  m_layout.setSpacing(0);
  m_layout.setMargin(0);  
  m_layout.setContentsMargins(0, 0, 0, 0);
  
  QSizePolicy spBoard(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spBoard.setVerticalStretch(9);
  m_frame.setSizePolicy(spBoard);
  m_layout.addWidget(&m_frame);

  QSizePolicy spChooser(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spChooser.setVerticalStretch(1);
  m_assetChooser.setSizePolicy(spChooser);
  m_layout.addWidget(&m_assetChooser);
  m_centralWidget.setLayout(&m_layout);

  m_board = new GameBoard(&m_frame);
  m_board->show();
}

void LevelEditor::keyPressEvent(QKeyEvent * event) 
{
  switch(event->key())
  {
    case ::Qt::Key::Key_Escape:
      QApplication::quit();
      break;
    default:
      QMainWindow::keyPressEvent(event);
      break;
  }
}

}
