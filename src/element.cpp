#include "element.h"
#include "level.h"
#include "screen.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp> 

#include <cassert>

namespace bigmama
{

Element::Element(const TexturePtr texture,
                 const sf::IntRect& rectangle)
  : m_texture{texture}, 
  m_sprite{*m_texture},
  m_rectangle{rectangle}
{ 
  sf::Vector2u size = texture->getSize(); 
  m_sprite.setPosition(m_rectangle.left, m_rectangle.top); 
  m_sprite.setScale(static_cast<float>(m_rectangle.width) / size.x, 
                    static_cast<float>(m_rectangle.height) / size.y);  
}

void Element::draw(::sf::RenderWindow& window) 
{
  window.draw(m_sprite);
}

} // namespace bigmama 
