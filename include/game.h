#ifndef BIGMAMAGAME_H
#define BIGMAMAGAME_H

#include "types.h"
#include "element.h"

#include <SFML/Graphics.hpp>

namespace bigmama
{

class AssetLibrary;
class Screen;
class Asset;

class Game
{
public:
  Game(const AssetLibrary& library,
       const Screen& screen,
       unsigned int levelNr = 1);
  void run();
private:
  void close();
  void display();
  void resize(const ::sf::Event& event);
  void keyPress(const ::sf::Event& event);
  void mousePress(const ::sf::Event& event);
  void drawStatusArea();
  void drawStatusAreaBorder(); 
  void printLevelEditModeIndicator();
  void drawGame();
  void reload(unsigned int levelNr);
  void toggleLevelEditMode(); 

private:
  ::sf::ContextSettings   m_settings;
  ::sf::VideoMode         m_mode;
  ::sf::RenderWindow      m_window;

  const AssetLibrary&     m_assets;
  const Screen&           m_screen; 
  std::vector<TexturePtr> m_textures;
  std::vector<ElementPtr> m_elements;
  unsigned int            m_levelNr; 
  bool                    m_levelEditMode;
 
  std::unique_ptr<Asset>  m_fontAsset;
  ::sf::Font              m_font; 
}; 

}

#endif // BIGMAMAGAME_H
