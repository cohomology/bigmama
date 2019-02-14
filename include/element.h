#ifndef BIGMAMASTATE_H
#define BIGMAMASTATE_H

#include "types.h"

#include <vector>
#include <SFML/Graphics.hpp>

namespace bigmama
{

class AssetLibrary;
class Screen;
class Resource;

class Element
{
public:
  Element(const Resource& resource,
          std::vector<TexturePtr>&& textures, 
          const ::sf::IntRect& rectangle); 
  Element(const Resource& resource,
          std::initializer_list<TexturePtr>&& textures,
          const ::sf::IntRect& rectangle);

  const Resource& resource() const 
  { return m_resource; }

  virtual void draw(::sf::RenderWindow& window) = 0; 

protected:
  const Resource&                m_resource;
  const std::vector<TexturePtr>  m_textures;
  ::sf::Sprite                   m_sprite;
  ::sf::IntRect                  m_rectangle; 
};

class SimpleElement : public Element
{
public:
  SimpleElement(const Resource& resource,
                TexturePtr&& textures, 
                const ::sf::IntRect& rectangle);  

  void draw(::sf::RenderWindow& window) override;
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
private:
  const AssetLibrary&     m_library;
  const Screen&           m_screen;
  std::vector<TexturePtr> m_textures;
  std::vector<ElementPtr> m_elements;
  unsigned int            m_level;
};

}

#endif // BIGMAMASTATE_H
