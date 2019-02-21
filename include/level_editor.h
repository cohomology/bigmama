#ifndef BIGMAMA_LEVEL_EDITOR_H
#define BIGMAMA_LEVEL_EDITOR_H

#include "game_board.h"
#include "asset_chooser_pane.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QFrame>

#include <memory>

namespace bigmama
{

class LevelEditor : public QMainWindow
{
  Q_OBJECT
public:
  LevelEditor(QWidget *parent = nullptr);
  void keyPressEvent(QKeyEvent *event) override;
private:
  QWidget          m_centralWidget;
  QFrame           m_frame; 
  GameBoard *      m_board;
  AssetChooserPane m_assetChooser;
  QVBoxLayout      m_layout;
  
};

}

#endif // BIGMAMA_LEVEL_EDITOR_H
