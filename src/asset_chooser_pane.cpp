#include "asset_chooser_pane.h"
#include "file_system.h"
#include "screen.h"
#include "resources.h"

#include <cassert>

namespace bigmama
{

AssetChooserPane::AssetChooserPane(const FileSystem& assets,
                                   const Screen& screen)
  : m_fileSystem(assets), m_screen(screen), m_editFrame(), m_editSprite(),
  m_frames(), m_resources(), m_offset(0), m_activeFrame(invalidFrame)
{
  auto asset = 
    assets.getAsset("level_edit_frame.png");
  m_editFrame.loadFromMemory(asset->data(), asset->size());
  m_editSprite.setTexture(m_editFrame);
  m_editSprite.setPosition(0, screen.height() - screen.statusAreaHeight());
  loadResources();
}

::sf::Vector2f AssetChooserPane::positionOfFrame(const Screen& screen, 
                                                 unsigned int frameNr)
{
 float x =  (frameNr + 1) * static_cast<float>(screen.width()) / (frameNumber + 1)  - frameSize / 2.0 - 1;
 float y = static_cast<float>(screen.height()) - screen.statusAreaHeight() / 2.0 
        - frameSize / 2.0 - 1; 
 return ::sf::Vector2f(x, y);
}

void AssetChooserPane::loadResources()
{
  for (unsigned int i = 0; i < frameNumber; ++i)
  {
    if (m_offset + i < resources.size())
    { 
      // draw frames
      m_frames[i] = std::make_optional<::sf::RectangleShape>();
      m_frames[i]->setSize(::sf::Vector2f(frameSize, frameSize));
      m_frames[i]->setOutlineColor(::sf::Color::Blue);
      m_frames[i]->setOutlineThickness(4);
      ::sf::Vector2f pos = positionOfFrame(m_screen, i);
      m_frames[i]->move(pos.x, pos.y); 

      // draw resources
      const Resource& resource = resources[m_offset + i];
      auto asset = m_fileSystem.getAsset(resource.textures()[0]);
      auto texture = std::make_shared<::sf::Texture>();
      texture->loadFromMemory(asset->data(), asset->size());
      ::sf::Sprite sprite;
      sf::Vector2u size = texture->getSize();  
      sprite.setTexture(*texture, true);
      sprite.setPosition(pos.x, pos.y);
      sprite.setScale(static_cast<float>(frameSize) / size.x, 
          static_cast<float>(frameSize) / size.y);    
      m_resources[i] = std::make_pair(texture, sprite);
    }
    else
    {
      m_frames[i].reset(); 
      m_resources[i] = TexturePair(nullptr, ::sf::Sprite());
    }
  } 
}

void AssetChooserPane::draw(::sf::RenderWindow& window) 
{
  window.draw(m_editSprite);
  for (auto& frame : m_frames)
    if (frame)
      window.draw(*frame);
  for (auto& resource : m_resources)
    window.draw(resource.second);
}

auto AssetChooserPane::mousePress(const ::sf::Vector2f& position) -> FrameArray::const_iterator 
{
  return std::find_if(m_frames.begin(), m_frames.end(), 
      [&position](const std::optional<::sf::RectangleShape>& frame) -> bool {
      return frame.has_value() && frame->getGlobalBounds().contains(position);
      });           
}

void AssetChooserPane::mousePressLeft(const ::sf::Vector2f& position)  
{
  auto frame = mousePress(position);
  if (frame != m_frames.end())
    activate(**frame, std::distance(m_frames.cbegin(), frame));
}

void AssetChooserPane::mousePressRight(const ::sf::Vector2f& position)  
{
  auto frame = mousePress(position);
  if (frame != m_frames.end())
  {
    auto frameNr = std::distance(m_frames.cbegin(), frame);
    if (frameNr == m_activeFrame)
      deactivateFrame();
  }
} 

void AssetChooserPane::deactivateFrame()
{
  assert(m_activeFrame < frameNumber);
  m_frames[m_activeFrame]->setOutlineColor(::sf::Color::Blue); 
  m_activeFrame = invalidFrame;
}

void AssetChooserPane::activate(const ::sf::RectangleShape& shape,
                           int frameNumber)
{
  if (frameSelected())
    deactivateFrame();
  m_activeFrame = frameNumber;
  m_frames[m_activeFrame]->setOutlineColor(::sf::Color::Red);  
}

std::pair<const Resource *, TexturePtr> AssetChooserPane::selectedResource()
{
  if (frameSelected())
    return std::make_pair(&resources[m_offset + m_activeFrame],
        m_resources[m_activeFrame].first);
  else 
    return std::pair<const Resource *, TexturePtr>(nullptr, nullptr);
}

void AssetChooserPane::keyPress(const ::sf::Event& event)
{
  switch(event.key.code)
  {
    case ::sf::Keyboard::Left:
    {
      if (m_offset > 0)
      {
        --m_offset;
        loadResources(); 
      }
      break;
    }
    case ::sf::Keyboard::Right:
    {
      if (m_offset + frameNumber < resources.size())
      {
        ++m_offset;
        loadResources(); 
      }
      break;
    }
  } 
}

};
