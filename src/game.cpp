#include "game.h"
#include "file_system.h"
#include "screen.h"
#include "level.h"
#include "resources.h"

#include <SFML/OpenGL.hpp>

#include <cassert>

namespace bigmama
{

Game::Game(const FileSystem& assets, 
           const Screen& screen,
           unsigned int levelNr)
  : AbstractGame{assets, screen, "bigmama"}, m_levelNr{levelNr}
{
  reload(levelNr);
  window().setMouseCursorVisible(false); 
}

void Game::reload(unsigned int levelNr) 
{
  AbstractGame::reload(levelNr);
  m_levelNr = levelNr;  
}

void Game::mousePress(const ::sf::Event& event)
{ }

void Game::mouseMoved(const ::sf::Event& event)
{ }

void Game::keyPress(const ::sf::Event& event)
{ }

} // namespace bigmama
