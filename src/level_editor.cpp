#include "level_editor.h"
#include "assets.h"
#include "screen.h"

namespace bigmama
{

LevelEditor::LevelEditor(const AssetLibrary& assets,
                         const Screen& screen)
{
  auto asset = 
    assets.get("level_edit_frame.png");
  m_editFrame.loadFromMemory(asset->data(), asset->size());
  m_editSprite.setTexture(m_editFrame);
  m_editSprite.setPosition(0, screen.height() - screen.statusAreaHeight());
}

void LevelEditor::draw(::sf::RenderWindow& window) 
{
  window.draw(m_editSprite);
}

};
