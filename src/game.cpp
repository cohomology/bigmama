#include "game.h"
#include "assets.h"
#include "screen.h"
#include "level.h"
#include "resources.h"

#include <SFML/OpenGL.hpp>

#include <cassert>

namespace bigmama
{

Game::Game(const AssetLibrary& assets, 
           const Screen& screen,
           unsigned int levelNr)
  : m_settings{16, 8, 8, 3, 0}, m_mode{screen.width(), screen.height()}, 
    m_window{m_mode, "bigmama", sf::Style::Fullscreen, m_settings},
     m_assets{assets}, m_screen{screen}, m_textureMap{},
  m_elements{}, m_levelNr{levelNr}, m_levelEditMode{false}, 
  m_fontAsset{m_assets.get("FreeMono.ttf")}, m_font{},
  m_editor{nullptr}, m_boundingRectangle{
      ::sf::Vector2f(m_screen.width(), m_screen.height() - m_screen.statusAreaHeight())},
  m_placedItem{}, m_placedItemHover{}
{
  m_window.setVerticalSyncEnabled(true);
  m_window.setActive(true); 
  m_font.loadFromMemory(m_fontAsset->data(), m_fontAsset->size());
  m_boundingRectangle.setOutlineColor(sf::Color::Black);
  m_boundingRectangle.setOutlineThickness(1);
  m_boundingRectangle.setPosition(0, 0); 
  reload(levelNr);
}

void Game::run()
{
  while (m_window.isOpen())
  {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          close();
          break;
        case sf::Event::Resized:
          resize(event);
          break;
        case sf::Event::KeyPressed:
          keyPress(event);
          break;
        case sf::Event::MouseButtonPressed:
          mousePress(event);
          break;
        case sf::Event::MouseMoved:
          mouseMoved(event);
          break;
      }
    }
    display();
  } 
} 

void Game::close()
{
  m_window.close();
} 

void Game::display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_window.clear(sf::Color::White);
  m_window.draw(m_boundingRectangle);
  drawStatusArea();
  drawGame();
  if (m_levelEditMode && m_placedItem.first != nullptr)
    m_window.draw(m_placedItemHover); 
  m_window.display(); 
}

void Game::resize(const sf::Event& event)
{
  glViewport(0, 0, event.size.width, event.size.height);
}

void Game::keyPress(const sf::Event& event)
{
  switch(event.key.code)
  {
    case sf::Keyboard::L:
      toggleLevelEditMode(); 
      break;
    case sf::Keyboard::Left:
    case sf::Keyboard::Right:
    case sf::Keyboard::Up:
    case sf::Keyboard::Down:
      // ????????????????????????????????
    case sf::Keyboard::Escape:
      close();
      break;
    default:
      break;
  }
} 

void Game::mousePress(const sf::Event& event)
{
  ::sf::Vector2i intPosition = sf::Mouse::getPosition(m_window);
  ::sf::Vector2f position = ::sf::Vector2f(intPosition.x, intPosition.y);
  switch(event.mouseButton.button)
  {
    case ::sf::Mouse::Left:
    {
      if (m_levelEditMode)
      {
        if (isInsideStatusArea(position))
        {
          assert(m_editor != nullptr);
          m_editor->mousePressLeft(position); 
        }
        else if (m_placedItem.first != nullptr)
        {
          ::sf::FloatRect bounds 
            = m_placedItemHover.getGlobalBounds();
          loadElement(*m_placedItem.first,
              ::sf::IntRect(bounds.left, bounds.top,
                bounds.width, bounds.height));
        }
      }
      break;
    }
    case ::sf::Mouse::Right:
    {
      if (m_levelEditMode && isInsideStatusArea(position))
      {
        assert(m_editor != nullptr);
        m_editor->mousePressRight(position);
      }
      break;
    }
  }
}

void Game::mouseMoved(const ::sf::Event& event)
{
  ::sf::Vector2u position = ::sf::Vector2u(event.mouseMove.x, 
      event.mouseMove.y);
  if (m_levelEditMode && isInsideGameArea(position) 
      && m_editor->frameSelected())
  {
    m_placedItem = m_editor->selectedResource();
    ::sf::Vector2u frameSize = m_placedItem.second->getSize();
    m_placedItemHover.setTexture(*m_placedItem.second, true);
    m_placedItemHover.setPosition(position.x - frameSize.x / 2, 
      position.y - frameSize.y / 2);
  }
  else
    m_placedItem = std::pair<const Resource *,
      TexturePtr>(nullptr, nullptr); 
} 

void Game::drawStatusArea()
{
  if (m_levelEditMode)
  {
    assert(m_editor != nullptr);
    m_editor->draw(m_window);
  }  
}

std::unique_ptr<Element> Game::createGameElement(
  const Resource& resource,
  std::vector<TexturePtr>&& textures,
  const ::sf::IntRect& rectangle)
{
  std::unique_ptr<Element> element;
  switch(resource.elementClassKind())
  {
    case ElementClassKind::SimpleElement:
    {
      assert(textures.size() == 1);
      element = std::make_unique<SimpleElement>(
          resource, std::move(textures[0]), rectangle);
      break;
    }
    default:
    {
      assert(1 == 0);
      break;
    }
  }
  return element;
}

void Game::reload(unsigned int levelNr)
{
  m_levelNr = levelNr; 
  m_textureMap.clear();
  m_elements.clear();
  Level level(m_assets, levelNr);
  std::map<const char *, TexturePtr, CompareString> textureMap;
  for (auto element : level.elements())
  {
    assert(element.resource < resources.size());
    const Resource& resource = resources[element.resource];
    loadElement(resource, ::sf::IntRect(element.x, element.y, 
          element.width, element.height));
  }
  m_window.setMouseCursorVisible(m_levelEditMode);
} 

void Game::loadElement(const Resource& resource,
                       const ::sf::IntRect& position) 
{
  std::vector<TexturePtr> textures;
  textures.reserve(resource.textures().size()); 
  for (auto& texture : resource.textures())
  {
    auto it = m_textureMap.find(texture);
    if (it != m_textureMap.end())
      textures.push_back(it->second);
    else
    {
      auto newTexture = std::make_shared<::sf::Texture>(); 
      auto asset = m_assets.get(texture);
      newTexture->loadFromMemory(asset->data(), asset->size());
      m_textureMap.insert(std::make_pair(texture, newTexture));
      textures.push_back(newTexture);
    }
  } 
  m_elements.push_back(createGameElement(resource, 
        std::move(textures), position));
}

void Game::drawGame()
{
  for(auto& element : m_elements)
    element->draw(m_window);
}

void Game::toggleLevelEditMode()
{
  m_levelEditMode = !m_levelEditMode;
  reload(m_levelEditMode ? 0 : 1);
  if (m_editor == nullptr)
    m_editor = std::make_unique<LevelEditor>(m_assets,
        m_screen);
}

} // namespace bigmama
