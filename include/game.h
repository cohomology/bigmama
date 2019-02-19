#ifndef BIGMAMAGAME_H
#define BIGMAMAGAME_H

#include "abstract_game.h"

namespace bigmama
{

class Game : public AbstractGame
{
public:
  Game(const FileSystem& library,
       const Screen& screen,
       unsigned int levelNr = 1);
protected:
  void reload(unsigned int levelNr) override; 
  void mousePress(const ::sf::Event& event) override; 
  void mouseMoved(const ::sf::Event& event) override;
  void keyPress(const ::sf::Event& event) override;
private:
  unsigned int m_levelNr; 
}; // class Game

} // namespace bigmama

#endif // BIGMAMAGAME_H
