#include "state.h"
#include "level.h"

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

void State::reload(unsigned int level)
{
//  Level level(m_library, level);
}

} // namespace bigmama 
