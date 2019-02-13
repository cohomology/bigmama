#include "game.h"
#include "assets.h"
#include "screen.h"
#include "level.h"

#include <SFML/OpenGL.hpp>
#include <cassert>

namespace bigmama
{

Game::Game(const AssetLibrary& assets, 
           const Screen& screen,
           unsigned int levelNr)
  : m_settings{16, 8, 8, 3, 0}, m_mode{screen.width(), screen.height()}, 
    m_window{m_mode, "bigmama", sf::Style::Fullscreen, m_settings},
    m_assets{assets}, m_screen{screen}, m_textures{},
  m_elements{}, m_levelNr{levelNr}             
{
  m_window.setVerticalSyncEnabled(true);
  m_window.setActive(true); 
  reload(levelNr);
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
          keyPress(event);
          break;
        case sf::Event::MouseButtonPressed:
          mousePress(event);
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
  drawStatusArea();
  drawGame();
  m_window.display(); 
}

void Game::resize(const sf::Event& event)
{
  glViewport(0, 0, event.size.width, event.size.height);
}

void Game::keyPress(const sf::Event& event)
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

void Game::mousePress(const sf::Event& event)
{
  switch(event.mouseButton.button)
  {
    case ::sf::Mouse::Left:
    case ::sf::Mouse::Right:
      break;
  }
}

void Game::drawStatusArea()
{
  ::sf::RectangleShape rectangle(
      ::sf::Vector2f(m_screen.width(), m_screen.height() - m_screen.statusAreaHeight()));
  rectangle.setOutlineColor(sf::Color::Black);
  rectangle.setOutlineThickness(1);
  rectangle.setPosition(0, 0);
  m_window.draw(rectangle);
}

void Game::reload(unsigned int levelNr)
{
  Level level(m_assets, levelNr);
  std::copy(level.textures().begin(), level.textures().end(),
      std::back_inserter(m_textures));
  for (auto wall : level.walls())
  {
    assert(wall.texture < m_textures.size());
    m_elements.push_back(std::make_unique<Element>(
          m_textures[wall.texture], 
          typename ::sf::IntRect(
            wall.x,
            wall.y,
            wall.width,
            wall.height)));
  }
} 

void Game::drawGame()
{
  for(auto& element : m_elements)
    element->draw(m_window);
}

} // namespace bigmama
