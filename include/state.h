#ifndef BIGMAMASTATE_H
#define BIGMAMASTATE_H

#include "types.h"

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
  ::sf::Sprite m_sprite;
  ::sf::IntRect m_rectangle;
};

class State
{
public:
  State(const AssetLibrary& library,
        unsigned int level = 1);
  void reload(unsigned int level);

private:
  const AssetLibrary&     m_library;
  std::vector<TexturePtr> m_textures;
  std::vector<Element>    m_elements;
  unsigned int            m_level;
};

}

#endif // BIGMAMASTATE_H
