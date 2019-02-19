#ifndef BIGMAMAASSETCHOOSERPANE_H
#define BIGMAMAASSETCHOOSERPANE_H 

#include "types.h"

#include <SFML/Graphics.hpp> 
#include <deque>
#include <optional>

namespace bigmama
{

class Screen;
class FileSystem;
class Resource;

class AssetChooserPane
{
  static constexpr unsigned int frameNumber = 10;
  static constexpr float frameSize = 64.0; 
  static constexpr int invalidFrame = -1;  

  typedef std::array<
    std::optional<::sf::RectangleShape>, frameNumber> FrameArray;
  typedef std::pair<TexturePtr, ::sf::Sprite> TexturePair;
  typedef std::array<TexturePair, frameNumber> TextureArray;
public:
  AssetChooserPane(const FileSystem& library,
                   const Screen& screen);

  void draw(::sf::RenderWindow& window);
  void mousePressLeft(const ::sf::Vector2f& position); 
  void mousePressRight(const ::sf::Vector2f& position);  
  void keyPress(const ::sf::Event& event);
  std::pair<const Resource *, TexturePtr> selectedResource(); 
  bool frameSelected() const
  { return m_activeFrame != invalidFrame; } 
private:
  void activate(const ::sf::RectangleShape& shape,
                int frameNumber); 
  void deactivateFrame();
  FrameArray::const_iterator mousePress(const ::sf::Vector2f& position);  
  void loadResources();  
  static ::sf::Vector2f positionOfFrame(const Screen& screen,
                                        unsigned int frameNr);
                                         

  const FileSystem& m_fileSystem;
  const Screen&       m_screen;
  ::sf::Texture       m_editFrame; 
  ::sf::Sprite        m_editSprite;
  FrameArray          m_frames;
  TextureArray        m_resources;
  unsigned int        m_offset;
  int                 m_activeFrame;
};

} // namespace bigmama
#endif // BIGMAMAASSETCHOOSERPANE_H
