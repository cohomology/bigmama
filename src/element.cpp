#include "element.h"
#include "level.h"

#include <QImage>
#include <QPainter>
#include <cassert>

namespace bigmama
{

Element::Element(const Resource& resource,
                 std::vector<TexturePtr>&& textures,
                 const QRect& rectangle)
  : m_resource(resource), m_textures{std::move(textures)}, m_sprite{},
  m_rectangle{rectangle}, m_currentTexture{0}
{ 
}

Element::Element(const Resource& resource,
                 std::initializer_list<TexturePtr>&& textures,
                 const QRect& rectangle)
  : m_resource{resource}, m_textures{std::move(textures)}, m_sprite{}, 
  m_rectangle{rectangle}, m_currentTexture{0}
{ } 

SimpleElement::SimpleElement(const Resource& resource,
                             TexturePtr&& texture, 
                             const QRect& rectangle)   
  : Element{resource, { std::move(texture) }, rectangle}
{
  const TexturePtr& myTexture = m_textures[0]; // don't take texture, content moved out!
  QSize size = myTexture->size(); 
  if (m_rectangle.width() != size.width() ||
      m_rectangle.height() != size.height())
    m_sprite = std::make_shared<QImage>(
        myTexture->scaled(static_cast<float>(m_rectangle.width()), 
                          static_cast<float>(m_rectangle.height())));    
  else
    m_sprite = myTexture;
}

void SimpleElement::draw(QPainter& painter) 
{
  assert(m_sprite != nullptr);
  painter.drawImage(m_rectangle.x(), 
      m_rectangle.y(), *m_sprite);
}

} // namespace bigmama 
