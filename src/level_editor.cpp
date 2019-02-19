#include "level_editor.h"
#include "file_system.h"
#include "screen.h"
#include "level.h"
#include "resources.h"

#include <SFML/OpenGL.hpp>

#include <cassert>
#include <fstream>

namespace bigmama
{

LevelEditor::LevelEditor(const FileSystem& assets, 
                         const Screen& screen)
  : AbstractGame(assets, screen, "bigmamalevel"), m_assetChooserPane(assets,
      screen), m_placedItem{}, m_placedItemHover{}, m_autoSaveTime{}
{
  reload(0);
}

void LevelEditor::display()
{
  AbstractGame::display();
  drawStatusArea();
  if (m_placedItem.first != nullptr)
    window().draw(m_placedItemHover); 
}

void LevelEditor::placeElement()
{
  if (m_placedItem.first != nullptr)
  {
    ::sf::FloatRect floatBounds 
      = m_placedItemHover.getGlobalBounds();
    ::sf::IntRect bounds(floatBounds.left, 
        floatBounds.top, floatBounds.width, 
        floatBounds.height); 
    placeElement(*m_placedItem.first, bounds);
  }
}

void LevelEditor::mousePress(const sf::Event& event)
{
  ::sf::Vector2i intPosition = sf::Mouse::getPosition(window());
  ::sf::Vector2f position = ::sf::Vector2f(intPosition.x, intPosition.y);
  switch(event.mouseButton.button)
  {
    case ::sf::Mouse::Left:
      mousePressLeft(position);
      break;
    case ::sf::Mouse::Right:
      mousePressRight(position);
      break;
  }
}

void LevelEditor::mousePressLeft(const ::sf::Vector2f& position)
{
  if (isInsideStatusArea(position))
    m_assetChooserPane.mousePressLeft(position); 
  else if (m_placedItem.first != nullptr)
    placeElement();
}

void LevelEditor::mousePressRight(const ::sf::Vector2f& position)
{
  if (isInsideStatusArea(position))
    m_assetChooserPane.mousePressRight(position);
  else
    deleteElementAtPosition(position);
}

void LevelEditor::mouseMoved(const ::sf::Event& event)
{
  ::sf::Vector2u position = ::sf::Vector2u(event.mouseMove.x, 
      event.mouseMove.y);
  if (isInsideGameArea(position) && m_assetChooserPane.frameSelected())
  {
    m_placedItem = m_assetChooserPane.selectedResource();
    ::sf::Vector2u frameSize = m_placedItem.second->getSize();
    m_placedItemHover.setSize(::sf::Vector2f(frameSize.x - 2, frameSize.y - 2));
    m_placedItemHover.setOutlineColor(::sf::Color::Black);
    m_placedItemHover.setFillColor(::sf::Color::Transparent); 
    m_placedItemHover.setOutlineThickness(1);
    m_placedItemHover.setPosition(
        position.x - ( position.x % frameSize.x ) + 1,
        position.y - ( position.y % frameSize.y ) + 1);
    if (::sf::Mouse::isButtonPressed(::sf::Mouse::Left))
      placeElement();
  }
  else
    m_placedItem = std::pair<const Resource *,
      TexturePtr>(nullptr, nullptr); 
  if (::sf::Mouse::isButtonPressed(::sf::Mouse::Right))
    deleteElementAtPosition(::sf::Vector2f(position.x, position.y)); 
} 

void LevelEditor::keyPress(const ::sf::Event& event)
{
  switch(event.key.code)
  {
    case ::sf::Keyboard::C:
      reload(0);
      break;
    default:
      m_assetChooserPane.keyPress(event); 
      break;
  } 
}

void LevelEditor::drawStatusArea()
{
  m_assetChooserPane.draw(window());
}

void LevelEditor::writeToFile(const char * fileName)
{
  ::Json::Value file;
  ::Json::Value elements(::Json::arrayValue);
  for (auto& e : this->elements())
  {
    const Resource * resource = &e->resource();
    const ::sf::IntRect& rectangle = e->rectangle();
    std::ptrdiff_t resourceNr = resource - &resources[0];
    assert(resourceNr >= 0);
    ::Json::Value element;
    element["resource"] = static_cast<unsigned>(resourceNr);
    element["x"] = rectangle.left;
    element["y"] = rectangle.top;
    element["width"] = rectangle.width;
    element["height"] = rectangle.height;
    elements.append(element);
  }
  file["elements"] = elements;
  std::ofstream ofs;
  ofs.open(fileName);
  ofs << file;
  ofs.close();
}

void LevelEditor::updateGame(const ::sf::Time& time) 
{
  m_autoSaveTime += time;
  unsigned seconds = m_autoSaveTime.asSeconds();
  if (seconds >= 10)
  {
    writeToFile(m_levelFileName);
    m_autoSaveTime = ::sf::seconds(0);
  }
}

void LevelEditor::close()
{
  writeToFile(m_levelFileName); 
}

const char * LevelEditor::m_levelFileName = "level.json";

} // namespace bigmama
