#ifndef BIGMAMALEVELEDITOR_H
#define BIGMAMALEVELEDITOR_H 

#include <SFML/Graphics.hpp> 

namespace bigmama
{

class Screen;
class AssetLibrary;

class LevelEditor
{
public:
  LevelEditor(const AssetLibrary& library,
              const Screen& screen);

  void draw(::sf::RenderWindow& window);

private:
  ::sf::Texture m_editFrame; 
  ::sf::Sprite  m_editSprite;
};

} // namespace bigmama
#endif // BIGMAMALEVELEDITOR
