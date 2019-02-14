#include "element.h"
#include "level.h"
#include "screen.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp> 

#include <cassert>

namespace bigmama
{

Element::Element(const Resource& resource,
                 std::vector<TexturePtr>&& textures,
                 const sf::IntRect& rectangle)
  : m_resource(resource), m_textures{std::move(textures)}, m_sprite{},
  m_rectangle{rectangle}
{ 
}

Element::Element(const Resource& resource,
                 std::initializer_list<TexturePtr>&& textures,
                 const ::sf::IntRect& rectangle)
  : m_resource{resource}, m_textures{std::move(textures)}, 
  m_rectangle{rectangle}
{ } 

SimpleElement::SimpleElement(const Resource& resource,
                             TexturePtr&& texture, 
                             const ::sf::IntRect& rectangle)   
  : Element{resource, { std::move(texture) }, rectangle}
{
  const TexturePtr& myTexture = m_textures[0]; // don't take texture, content moved out!
  sf::Vector2u size = myTexture->getSize(); 
  m_sprite.setTexture(*myTexture, true);
  m_sprite.setPosition(m_rectangle.left, m_rectangle.top); 
  m_sprite.setScale(static_cast<float>(m_rectangle.width) / size.x, 
                    static_cast<float>(m_rectangle.height) / size.y);   
}

void SimpleElement::draw(::sf::RenderWindow& window) 
{
  window.draw(m_sprite);
}

} // namespace bigmama 
