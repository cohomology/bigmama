#ifndef BIGMAMA_LEVEL_EDITOR_H
#define BIGMAMA_LEVEL_EDITOR_H

#include "game_board_edit.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <memory>

QT_FORWARD_DECLARE_CLASS(QScrollArea)

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
  void shrinkToFitAction(bool checked);

private:
  void createActions();
  void createLayout();  
  void createMenus();
  void createToolbar();
  void saveLevelAs(const QString& fileName);
  void openFile(const QString& fileName);
  void chooseAsset(const Resource& resource,
                   const QAction& triggeringAction);
  void shrinkToFit();
  void enableScrolling();

  FileSystem&       m_fileSystem;
  QScrollArea *     m_scrollArea;
  EditableGameBoard m_board;
  QWidget *         m_centralWidget;
  QVBoxLayout *     m_layout;
  QMenu *           m_fileMenu;
  QMenu *           m_viewMenu;
  QMenu *           m_helpMenu;
  QToolBar *        m_assetChooser;
  QAction *         m_exitAction;
  QAction *         m_newAction;
  QAction *         m_openAction;
  QAction *         m_saveAction;
  QAction *         m_saveAsAction;
  QAction *         m_aboutQt;
  QAction *         m_shrinkToFitAction;
  QString           m_levelFileName;
};

}

#endif // BIGMAMA_LEVEL_EDITOR_H
