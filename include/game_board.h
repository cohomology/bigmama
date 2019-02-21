#ifndef BIGMAMA_GAME_BOARD_H
#define BIGMAMA_GAME_BOARD_H

#include "sfml_canvas.h"

namespace bigmama
{

class GameBoard : public SFMLCanvas
{
  Q_OBJECT
public:
  GameBoard(QWidget *parent = nullptr);

protected:
  void onInit() override;
  void onUpdate() override; 
};

}

#endif // BIGMAMA_GAME_BOARD_H
