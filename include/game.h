#ifndef BIGMAMAGAME_H
#define BIGMAMAGAME_H

#include <SFML/Graphics.hpp>

namespace bigmama
{

class AssetLibrary;
class State;
class Screen;

class Game
{
public:
  Game(const AssetLibrary& library,
       const Screen& screen,
       State& state);
  void run();
private:
  void close();
  void display();
  void resize(const ::sf::Event& event);
  void keypress(const ::sf::Event& event);

private:
  ::sf::ContextSettings m_settings;
  ::sf::VideoMode       m_mode;
  ::sf::RenderWindow    m_window;
  const AssetLibrary&   m_assets;
  const Screen&         m_screen;
  State&                m_state; 
}; 

}

#endif // BIGMAMAGAME_H
