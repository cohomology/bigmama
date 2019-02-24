#ifndef BIGMAMA_GAME_BOARD_EDIT_H
#define BIGMAMA_GAME_BOARD_EDIT_H

#include "game_board.h"

namespace bigmama
{

class EditableGameBoard : public GameBoard
{
  Q_OBJECT

public:
  EditableGameBoard(FileSystem& fileSystem, 
      QWidget *parent = nullptr) :
    GameBoard(fileSystem, parent)
  { }

protected:
  void mouseMoveEvent(QMouseEvent *event) override;
};

}

#endif // BIGMAMA_GAME_BOARD_EDIT_H
