#ifndef BIGMAMALEVELEDITOR_H
#define BIGMAMALEVELEDITOR_H 

#include "types.h"

#include <SFML/Graphics.hpp> 
#include <deque>

namespace bigmama
{

class Screen;
class AssetLibrary;
class Resource;

class LevelEditor
{
  static constexpr unsigned int frameNumber = 10;
  static constexpr float frameSize = 64.0; 
  static constexpr int invalidFrame = -1;  

  typedef std::array<::sf::RectangleShape, frameNumber> FrameArray;
  typedef std::array<
    std::pair<TexturePtr, ::sf::Sprite>, frameNumber> TextureArray;
public:
  LevelEditor(const AssetLibrary& library,
              const Screen& screen);

  void draw(::sf::RenderWindow& window);
  void mousePressLeft(const ::sf::Vector2f& position); 
  void mousePressRight(const ::sf::Vector2f& position);  
  std::pair<const Resource *, TexturePtr> selectedResource(); 
  bool frameSelected() const
  { return m_activeFrame != invalidFrame; } 
private:
  void activate(const ::sf::RectangleShape& shape,
                int frameNumber); 
  void deactivateFrame();
  FrameArray::const_iterator mousePress(const ::sf::Vector2f& position);  

  const AssetLibrary& m_assets;
  ::sf::Texture       m_editFrame; 
  ::sf::Sprite        m_editSprite;
  FrameArray          m_frames;
  TextureArray        m_resources;
  unsigned int        m_offset;
  int                 m_activeFrame;
};

} // namespace bigmama
#endif // BIGMAMALEVELEDITOR
