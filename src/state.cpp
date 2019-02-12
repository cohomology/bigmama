#include "state.h"
#include "level.h"

#include <SFML/Graphics/Rect.hpp>
#include <cassert>

namespace bigmama
{

Element::Element(const TexturePtr texture,
                 const sf::IntRect& rectangle)
  : m_texture{texture}, m_sprite{*m_texture.get()},
  m_rectangle{rectangle}
{
  sf::Vector2u size = texture->getSize();
  m_sprite.setPosition(rectangle.left, rectangle.top); 
  m_sprite.setScale(rectangle.width / size.x, 
                    rectangle.height / size.y);
}

void Element::draw(::sf::RenderWindow& window) 
{
  window.draw(m_sprite);
}

State::State(const AssetLibrary& library,
             unsigned int level) 
  : m_library(library), m_textures(), m_elements(),
  m_level(level)
{
  reload(level);
}

void State::reload(unsigned int levelNr)
{
  Level level(m_library, levelNr);
  for (auto texture : level.textures())
    m_textures.push_back(texture);
  for (auto wall : level.walls())
  {
    assert(wall.texture < m_textures.size());
    m_elements.push_back(std::make_unique<Element>(
          m_textures[wall.texture], 
          typename ::sf::IntRect(
            level.grid_size()*wall.x,
            level.grid_size()*wall.y,
            level.grid_size(),
            level.grid_size())));
  }
}

} // namespace bigmama 
