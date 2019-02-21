#include "game_board.h"

namespace bigmama
{

GameBoard::GameBoard(QWidget *parent)
  : SFMLCanvas(parent)
{ 
}

void GameBoard::onInit()
{
}

void GameBoard::onUpdate()
{
  // Clear screen
  clear(sf::Color(0, 0, 0));
}

}
