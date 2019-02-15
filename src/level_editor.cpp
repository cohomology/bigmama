#include "level_editor.h"
#include "assets.h"
#include "screen.h"
#include "resources.h"

#include <cassert>

namespace bigmama
{

LevelEditor::LevelEditor(const AssetLibrary& assets,
                         const Screen& screen)
  : m_assets(assets), m_editFrame(), m_editSprite(),
  m_frames(), m_resources(), m_offset(0), m_activeFrame(invalidFrame)
{
  auto asset = 
    assets.get("level_edit_frame.png");
  m_editFrame.loadFromMemory(asset->data(), asset->size());
  m_editSprite.setTexture(m_editFrame);
  m_editSprite.setPosition(0, screen.height() - screen.statusAreaHeight());
  for (unsigned int i = 0; i < frameNumber; ++i)
  {
    // draw frames
    m_frames[i].setSize(::sf::Vector2f(frameSize, frameSize));
    m_frames[i].setOutlineColor(::sf::Color::Blue);
    m_frames[i].setOutlineThickness(4);
    float x =  (i + 1) * static_cast<float>(screen.width()) / (frameNumber + 1)  - frameSize / 2.0 - 1;
    float y = static_cast<float>(screen.height()) - screen.statusAreaHeight() / 2.0 
      - frameSize / 2.0 - 1;
    m_frames[i].move(x, y);

    // draw resources
    if (m_offset + i < resources.size())
    {
      const Resource& resource = resources[m_offset + i];
      auto asset = m_assets.get(resource.textures()[0]);
      auto texture = std::make_shared<::sf::Texture>();
      texture->loadFromMemory(asset->data(), asset->size());
      ::sf::Sprite sprite;
      sf::Vector2u size = texture->getSize();  
      sprite.setTexture(*texture, true);
      sprite.setPosition(x, y);
      sprite.setScale(static_cast<float>(frameSize) / size.x, 
          static_cast<float>(frameSize) / size.y);    
      m_resources[i] = std::make_pair(texture, sprite);
    }
  }
}

void LevelEditor::draw(::sf::RenderWindow& window) 
{
  window.draw(m_editSprite);
  for (auto& frame : m_frames)
    window.draw(frame);
  for (auto& resource : m_resources)
    window.draw(resource.second);
}

auto LevelEditor::mousePress(const ::sf::Vector2f& position) -> FrameArray::const_iterator 
{
  return std::find_if(m_frames.begin(), m_frames.end(), 
      [&position](const ::sf::Shape& frame) -> bool {
      return frame.getGlobalBounds().contains(position);
      });           
}

void LevelEditor::mousePressLeft(const ::sf::Vector2f& position)  
{
  auto frame = mousePress(position);
  if (frame != m_frames.end())
    activate(*frame, std::distance(m_frames.cbegin(), frame));
}

void LevelEditor::mousePressRight(const ::sf::Vector2f& position)  
{
  auto frame = mousePress(position);
  if (frame != m_frames.end())
  {
    auto frameNr = std::distance(m_frames.cbegin(), frame);
    if (frameNr == m_activeFrame)
      deactivateFrame();
  }
} 

void LevelEditor::deactivateFrame()
{
  assert(m_activeFrame < frameNumber);
  m_frames[m_activeFrame].setOutlineColor(::sf::Color::Blue); 
  m_activeFrame = invalidFrame;
}

void LevelEditor::activate(const ::sf::RectangleShape& shape,
                           int frameNumber)
{
  if (frameSelected())
    deactivateFrame();
  m_activeFrame = frameNumber;
  m_frames[m_activeFrame].setOutlineColor(::sf::Color::Red);  
}

};
