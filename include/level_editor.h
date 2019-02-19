#ifndef BIGMAMALEVELEDITOR_H
#define BIGMAMALEVELEDITOR_H

#include "abstract_game.h"
#include "asset_chooser_pane.h"

namespace bigmama
{

class LevelEditor : public AbstractGame
{
public:
  LevelEditor(const FileSystem& library,
              const Screen& screen);

protected:
  void display() override;
  void mousePress(const sf::Event& event) override; 
  void mouseMoved(const ::sf::Event& event) override; 
  void updateGame(const ::sf::Time& time) override;
  void keyPress(const ::sf::Event& event) override; 
  void close() override; 
  using AbstractGame::placeElement;

private:
  void mousePressLeft(const ::sf::Vector2f& position); 
  void mousePressRight(const ::sf::Vector2f& position); 
  void drawStatusArea(); 
  void placeElement();
  void writeToFile(const char * fileName); 

private:
  AssetChooserPane             m_assetChooserPane;
  std::pair<const Resource *,
    TexturePtr      >          m_placedItem;
  ::sf::RectangleShape         m_placedItemHover;
  ::sf::Time                   m_autoSaveTime;

  static const char * m_levelFileName;
}; // class LevelEditor

} // namespace bigmama

#endif // BIGMAMALEVELEDITOR_H
