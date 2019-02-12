#ifndef BIGMAMASTATE_H
#define BIGMAMASTATE_H

#include "types.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace bigmama
{

class AssetLibrary;
class Screen;

class Element
{
public:
  Element(const TexturePtr texture,
          const ::sf::IntRect& rectable);

  void draw(::sf::RenderWindow& window);

private:
  const TexturePtr m_texture;
  ::sf::Sprite m_sprite;
  ::sf::IntRect m_rectangle;
};

typedef std::unique_ptr<Element> ElementPtr;

class State
{
public:
  State(const AssetLibrary& library,
        const Screen& screen,
        unsigned int level = 1);
  void reload(unsigned int level);
  void drawWalls(::sf::RenderWindow& window);
  void drawBoundingBox(::sf::RenderWindow& window);
private:
  void computeLevelBoundingBox(); 

  const AssetLibrary&     m_library;
  const Screen&           m_screen;
  std::vector<TexturePtr> m_textures;
  std::vector<ElementPtr> m_elements;
  unsigned int            m_level;
  unsigned int            m_xBoxCnt;
  unsigned int            m_yBoxCnt;
  ::sf::IntRect           m_drawingArea;
  unsigned int            m_gridSize; 
};

}

#endif // BIGMAMASTATE_H
