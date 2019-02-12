#include "state.h"
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

State::State(const AssetLibrary& library,
             const Screen& screen, 
             unsigned int level) 
  : m_library{library}, m_screen{screen}, m_textures{},
  m_elements{}, m_level{level}, m_xBoxCnt{0}, m_yBoxCnt{0}, 
  m_drawingArea{}, m_gridSize{0}
{
  reload(level);
}

void State::reload(unsigned int levelNr)
{
  Level level(m_library, levelNr);
  m_xBoxCnt = level.xBoxCnt();
  m_yBoxCnt = level.yBoxCnt();
  computeLevelBoundingBox();  
  std::copy(level.textures().begin(), level.textures().end(),
      std::back_inserter(m_textures));
  for (auto wall : level.walls())
  {
    assert(wall.texture < m_textures.size());
    m_elements.push_back(std::make_unique<Element>(
          m_textures[wall.texture], 
          typename ::sf::IntRect(
            m_drawingArea.left + m_gridSize * wall.x,
            m_drawingArea.top + m_gridSize * wall.y,
            m_gridSize,
            m_gridSize)));
  }
}

void State::drawWalls(::sf::RenderWindow& window)
{
  for (auto& element : m_elements)
    element->draw(window);
}

void State::computeLevelBoundingBox()
{
  unsigned int maxXbox = (m_screen.width() - 2 * m_screen.minLeftBorder()) / m_xBoxCnt;
  unsigned int maxYbox = (m_screen.height() - 2 * m_screen.minTopBorder()) / m_yBoxCnt;
  m_gridSize = std::min(maxXbox, maxYbox);
  unsigned int width = m_gridSize * m_xBoxCnt;
  unsigned int height = m_gridSize * m_yBoxCnt;
  unsigned int left = m_screen.width() / 2 - width / 2;
  unsigned int right = m_screen.height() / 2 - height / 2;
  m_drawingArea = ::sf::IntRect(left, right, width, height);
} 

} // namespace bigmama 
