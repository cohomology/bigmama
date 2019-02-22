#ifndef BIGMAMA_LEVEL_EDITOR_H
#define BIGMAMA_LEVEL_EDITOR_H

#include "game_board.h"
#include "asset_chooser_pane.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <memory>

namespace bigmama
{

class FileSystem;

class LevelEditor : public QMainWindow
{
  Q_OBJECT
public:
  LevelEditor(FileSystem& fileSystem, 
              QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent *event) override;
private slots:
  void newAction();
  void openAction();
  void saveAction();
  void saveAsAction();

private:
  void createActions();
  void createLayout();  
  void createMenus();
  void saveLevelAs(const QString& fileName);
  void openFile(const QString& fileName);

  FileSystem&       m_fileSystem;
  QWidget           m_centralWidget;
  GameBoard         m_board;
  AssetChooserPane  m_assetChooser;
  QVBoxLayout       m_layout;
  QMenu *           m_fileMenu;
  QMenu *           m_helpMenu;
  QAction *         m_exitAction;
  QAction *         m_newAction;
  QAction *         m_openAction;
  QAction *         m_saveAction;
  QAction *         m_saveAsAction;
  QAction *         m_aboutQt;
  QString           m_levelFileName;
};

}

#endif // BIGMAMA_LEVEL_EDITOR_H
