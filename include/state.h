#ifndef BIGMAMASTATE_H
#define BIGMAMASTATE_H

#include "texture.h"

#include <vector>

#include <SFML/Graphics.hpp>

namespace bigmama
{

class AssetLibrary;

class Element
{
public:
  Element(const TexturePtr texture,
          const ::sf::IntRect& rectable);

  void draw(::sf::RenderWindow& window);

private:
  const TexturePtr m_texture;
  ::sf::IntRect m_rectangle;
};

typedef std::unique_ptr<Element> ElementPtr;

class State
{
public:
  State(const AssetLibrary& library,
        unsigned int level = 1);
  void reload(unsigned int level);
  void drawWalls(::sf::RenderWindow& window);
private:
  const AssetLibrary&     m_library;
  std::vector<TexturePtr> m_textures;
  std::vector<ElementPtr> m_elements;
  unsigned int            m_level;
};

}

#endif // BIGMAMASTATE_H
