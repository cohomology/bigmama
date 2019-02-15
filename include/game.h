#ifndef BIGMAMAGAME_H
#define BIGMAMAGAME_H

#include "types.h"
#include "element.h"
#include "level_editor.h"
#include "screen.h"

#include <SFML/Graphics.hpp>
#include <cstring> 

namespace bigmama
{

class AssetLibrary;
class Screen;
class Asset;
class LevelEditor;

struct CompareString
{
  bool operator()(const char * first, const char * second) const
  { return std::strcmp(first, second) < 0; }
}; 

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
  void mouseMoved(const ::sf::Event& event);
  void drawStatusArea();
  void drawStatusAreaBorder(); 
  void drawGame();
  void reload(unsigned int levelNr);
  void toggleLevelEditMode(); 
  std::unique_ptr<Element> createGameElement(
      const Resource& resource,
      std::vector<TexturePtr>&& textures,
      const ::sf::IntRect& rectangle); 
  template<typename T>
  bool isInsideStatusArea(const ::sf::Vector2<T>& position)
  { return position.y >= m_screen.height() - m_screen.statusAreaHeight(); }
  template<typename T>
  bool isInsideGameArea(const ::sf::Vector2<T>& position)
  { return !isInsideStatusArea(position); }
  void loadElement(const Resource& resource,
                   const ::sf::IntRect& position);

private:
  ::sf::ContextSettings        m_settings;
  ::sf::VideoMode              m_mode;
  ::sf::RenderWindow           m_window;

  const AssetLibrary&          m_assets;
  const Screen&                m_screen; 
  std::map<const char *, 
    TexturePtr, CompareString> m_textureMap; 
  std::vector<ElementPtr>      m_elements;
  unsigned int                 m_levelNr; 
  bool                         m_levelEditMode;
 
  std::unique_ptr<Asset>       m_fontAsset;
  ::sf::Font                   m_font; 

  std::unique_ptr<LevelEditor> m_editor;
  ::sf::RectangleShape         m_boundingRectangle;
  
  std::pair<const Resource *,
    TexturePtr      >          m_placedItem;
  ::sf::Sprite                 m_placedItemHover;
}; 

}

#endif // BIGMAMAGAME_H
