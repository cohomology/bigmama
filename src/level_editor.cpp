#include "level_editor.h"
#include "file_system.h"

#include <QKeyEvent>
#include <QApplication>

namespace bigmama
{

LevelEditor::LevelEditor(FileSystem& fileSystem, QWidget *parent)
    : QMainWindow(parent), 
    m_fileSystem(fileSystem), m_centralWidget(), m_board(fileSystem), 
    m_assetChooser(), m_layout()
{
  setCentralWidget(&m_centralWidget);  

  m_layout.setSpacing(0);
  m_layout.setMargin(0);  
  m_layout.setContentsMargins(0, 0, 0, 0);
  
  QSizePolicy spBoard(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spBoard.setVerticalStretch(9);
  m_board.setSizePolicy(spBoard);
  m_layout.addWidget(&m_board);

  QSizePolicy spChooser(QSizePolicy::Preferred, QSizePolicy::Preferred);
  spChooser.setVerticalStretch(1);
  m_assetChooser.setSizePolicy(spChooser);
  m_layout.addWidget(&m_assetChooser);
  m_centralWidget.setLayout(&m_layout);
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
