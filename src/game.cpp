#include "game.h"
#include "assets.h"
#include "state.h"
#include "screen.h"

#include <SFML/OpenGL.hpp>

namespace bigmama
{

Game::Game(const Screen& screen,
           State& state)
  : m_settings{16, 8, 8, 3, 0}, m_mode{screen.width(), screen.height()}, 
    m_window{m_mode, "bigmama", sf::Style::Fullscreen, m_settings},
    m_screen{screen}, m_state{state} 
{
  m_window.setVerticalSyncEnabled(true);
  m_window.setActive(true); 
}

void Game::run()
{
  while (m_window.isOpen())
  {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          close();
          break;
        case sf::Event::Resized:
          resize(event);
          break;
        case sf::Event::KeyPressed:
          keypress(event);
          break;
      }
    }
    display();
  } 
} 

void Game::close()
{
  m_window.close();
} 

void Game::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_window.clear(sf::Color::White);
  m_state.drawWalls(m_window);
  m_window.display(); 
}

void Game::resize(const sf::Event& event)
{
  glViewport(0, 0, event.size.width, event.size.height);
}

void Game::keypress(const sf::Event& event)
{
  switch(event.key.code)
  {
    case sf::Keyboard::Left:
    case sf::Keyboard::Right:
    case sf::Keyboard::Up:
    case sf::Keyboard::Down:
      // ????????????????????????????????
    case sf::Keyboard::Escape:
      close();
      break;
    default:
      break;
  }
} 

} // namespace bigmama
