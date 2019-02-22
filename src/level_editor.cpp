#include "level_editor.h"
#include "file_system.h"

#include <QKeyEvent>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction> 
#include <QMessageBox>

namespace bigmama
{

LevelEditor::LevelEditor(FileSystem& fileSystem, QWidget *parent)
    : QMainWindow(parent), 
    m_fileSystem(fileSystem), m_centralWidget(), m_board(fileSystem), 
    m_assetChooser(), m_layout(), m_fileMenu(), m_helpMenu(),
    m_exitAction()
{
  setCentralWidget(&m_centralWidget);  
  createLayout();
  createActions();
  createMenus();
}

void LevelEditor::createLayout()
{
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

void LevelEditor::createActions()
{
  m_exitAction = new QAction(tr("E&xit"), this);
  m_exitAction->setShortcuts(QKeySequence::Quit);
  m_exitAction->setMenuRole(QAction::QuitRole);
  m_exitAction->setStatusTip(tr("Exit the application"));
  connect(m_exitAction, &QAction::triggered, this, &QWidget::close);

  m_aboutQt = new QAction(tr("About &Qt"), this);
  m_exitAction->setMenuRole(QAction::AboutQtRole);
  m_exitAction->setStatusTip(tr("About Qt"));
  connect(m_aboutQt, &QAction::triggered, this, 
      std::bind(&QMessageBox::aboutQt, this, tr("About Qt")));
}


void LevelEditor::createMenus()
{
  m_fileMenu = menuBar()->addMenu(tr("&File"));
  m_fileMenu->addSeparator();
  m_fileMenu->addAction(m_exitAction);

  m_helpMenu = menuBar()->addMenu(tr("&Help"));
  m_helpMenu->addAction(m_aboutQt); 
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
