#include "level_editor.h"
#include "file_system.h"
#include "resources.h"

#include <QKeyEvent>
#include <QApplication>
#include <QMenuBar>
#include <QMenu>
#include <QAction> 
#include <QMessageBox>
#include <QFileDialog>
#include <QScrollArea>
#include <QToolBar>

namespace bigmama
{

LevelEditor::LevelEditor(FileSystem& fileSystem, QWidget *parent)
    : QMainWindow(parent), 
    m_fileSystem(fileSystem), m_board(fileSystem), 
    m_fileMenu(), m_helpMenu(), m_exitAction()
{
  createLayout();
  createActions();
  createMenus();
  createToolbar();
}

void LevelEditor::createLayout()
{
  setWindowState(Qt::WindowMaximized);
  m_scrollArea = new QScrollArea(this);
  m_scrollArea->setWidgetResizable(true);
  
  shrinkToFit();
  m_scrollArea->setWidget(&m_board); 

  m_centralWidget = new QWidget;
  setCentralWidget(m_centralWidget); 
  m_layout = new QVBoxLayout;

  m_centralWidget->setLayout(m_layout);
  m_layout->addWidget(m_scrollArea);
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

  m_shrinkToFitAction = new QAction(tr("S&hrink to fit"), this);
  m_shrinkToFitAction->setCheckable(true);
  m_shrinkToFitAction->setChecked(true);
  connect(m_shrinkToFitAction, &QAction::triggered, this, 
      &LevelEditor::shrinkToFitAction);
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

  m_viewMenu = menuBar()->addMenu(tr("&View"));
  m_viewMenu->addAction(m_shrinkToFitAction);

  m_helpMenu = menuBar()->addMenu(tr("&Help"));
  m_helpMenu->addAction(m_aboutQt); 
} 

void LevelEditor::createToolbar()
{
  m_assetChooser = new QToolBar;
  m_assetChooser->setIconSize(QSize(32, 32));
  m_assetChooser->setToolButtonStyle(Qt::ToolButtonIconOnly); 
  m_layout->addWidget(m_assetChooser);
  for (auto& resource : resources)
  {
    assert(!resource.textures().empty());
    auto asset = m_fileSystem.getAsset(
        *resource.textures().begin());
    QImage image; 
    image.loadFromData( 
       reinterpret_cast<const uchar*>(asset->data()), 
       asset->size()); 
    QPixmap pixmap;
    pixmap.convertFromImage(image);
    QAction * action = m_assetChooser->addAction(QIcon(pixmap),
        QString(resource.description()));
    connect(action, &QAction::triggered, this, 
        [this, &resource, action](bool checked) {
        if (checked)
          chooseAsset(resource, *action);
    });
    action->setCheckable(true);
  }
}

void LevelEditor::chooseAsset(const Resource& resource,
                              const QAction& triggeringAction)
{
  for (auto& action: m_assetChooser->actions())
  {
    if (action != &triggeringAction)
      action->setChecked(false);
  }
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

void LevelEditor::shrinkToFitAction(bool enabled)
{
  enabled ? shrinkToFit() : enableScrolling();
  m_board.repaint(); 
}

void LevelEditor::shrinkToFit()
{
  m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); 
  m_board.shrinkToFit(true);
}

void LevelEditor::enableScrolling()
{
  m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
  m_board.shrinkToFit(false);
}

}
