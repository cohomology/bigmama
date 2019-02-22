#include "level_editor.h"
#include "file_system.h"

#include <QKeyEvent>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction> 
#include <QMessageBox>
#include <QFileDialog>

namespace bigmama
{

LevelEditor::LevelEditor(FileSystem& fileSystem, QWidget *parent)
    : QMainWindow(parent), 
    m_fileSystem(fileSystem), m_centralWidget(), m_board(fileSystem), 
    m_assetChooser(), m_layout(), m_fileMenu(), m_helpMenu(),
    m_exitAction()
{
  setCentralWidget(&m_board);  
  // createLayout();
  createActions();
  createMenus();
}

void LevelEditor::createLayout()
{
  m_layout.setSpacing(0);
  m_layout.setMargin(0);  
  m_layout.setContentsMargins(0, 0, 0, 0);

  /* QSizePolicy spBoard(QSizePolicy::Preferred, QSizePolicy::Preferred); */
  /* spBoard.setVerticalStretch(9); */
  /* m_board.setSizePolicy(spBoard); */
  m_layout.addWidget(&m_board);

  /* QSizePolicy spChooser(QSizePolicy::Preferred, QSizePolicy::Preferred); */
  /* spChooser.setVerticalStretch(1); */
  /* m_assetChooser.setSizePolicy(spChooser); */
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

  m_newAction = new QAction(tr("&New level"), this);
  m_newAction->setShortcuts(QKeySequence::New);
  m_newAction->setStatusTip(tr("New level"));
  connect(m_newAction, &QAction::triggered, this, 
      &LevelEditor::newAction);

  m_openAction = new QAction(tr("&Open level"), this);
  m_openAction->setShortcuts(QKeySequence::Open);
  m_openAction->setStatusTip(tr("Open level"));
  connect(m_openAction, &QAction::triggered, this, 
      &LevelEditor::openAction);  

  m_saveAction = new QAction(tr("&Save level"), this);
  m_saveAction->setShortcuts(QKeySequence::Save);
  m_saveAction->setStatusTip(tr("Save level"));
  connect(m_saveAction, &QAction::triggered, this, 
      &LevelEditor::saveAction); 

  m_saveAsAction = new QAction(tr("&Save as ..."), this);
  m_saveAsAction->setShortcuts(QKeySequence::SaveAs);
  m_saveAsAction->setStatusTip(tr("Save level as ..."));
  connect(m_saveAsAction, &QAction::triggered, this, 
      &LevelEditor::saveAsAction);  
  m_saveAsAction->setEnabled(false);

  m_aboutQt = new QAction(tr("About &Qt"), this);
  m_exitAction->setMenuRole(QAction::AboutQtRole);
  m_exitAction->setStatusTip(tr("About Qt"));
  connect(m_aboutQt, &QAction::triggered, this, 
      std::bind(&QMessageBox::aboutQt, this, tr("About Qt")));
}


void LevelEditor::createMenus()
{
  m_fileMenu = menuBar()->addMenu(tr("&File"));
  m_fileMenu->addAction(m_newAction);
  m_fileMenu->addAction(m_openAction);
  m_fileMenu->addAction(m_saveAction); 
  m_fileMenu->addAction(m_saveAsAction);  
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

void LevelEditor::newAction()
{

}

void LevelEditor::openAction()
{
  QString fileName = QFileDialog::getOpenFileName(this,
      tr("Open level"), QDir::homePath().toUtf8(),
      tr("Level file (*.mama)")); 
  if (!fileName.isEmpty())
  {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) 
    {
      QMessageBox::information(this, tr("Unable to open file"),
          file.errorString());
    }
    m_levelFileName = fileName;
    m_saveAsAction->setEnabled(true); 
  } 
}

void LevelEditor::saveAction()
{
  if (m_levelFileName.isEmpty())
    saveAsAction();
  else
  {
    saveLevelAs(m_levelFileName);
  }
}

void LevelEditor::saveAsAction()
{
  QString fileName = QFileDialog::getSaveFileName(this,
      tr("Save level as ..."), QDir::homePath().toUtf8(),
      tr("Level file (*.mama)"));
  if (!fileName.isEmpty())
  {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) 
    {
      QMessageBox::information(this, tr("Unable to open file"),
          file.errorString());
    }
    m_levelFileName = fileName;
    m_saveAsAction->setEnabled(true); 
    saveLevelAs(m_levelFileName); 
  }
}

void LevelEditor::saveLevelAs(const QString& fileName) 
{

}

void LevelEditor::openFile(const QString& filename)
{

}

}
