#include "abstract_game.h"
#include "file_system.h"
#include "resources.h"
#include "level.h"

#include <SFML/OpenGL.hpp> 
#include <cassert>

namespace bigmama
{

AbstractGame::AbstractGame(const FileSystem& assets, 
                           const Screen& screen,
                           const char * executable) 
  : m_settings{16, 8, 8, 3, 0}, m_mode{screen.width(), screen.height()}, 
  m_window{m_mode, executable, sf::Style::Fullscreen, m_settings},
  m_fileSystem{assets}, m_screen{screen}, m_textureMap{},
  m_elements{}, m_fontAsset{m_fileSystem.getAsset("FreeMono.ttf")}, m_font{},
  m_boundingRectangle{
      ::sf::Vector2f(m_screen.width(), m_screen.height() - m_screen.statusAreaHeight())} 
{
  m_window.setVerticalSyncEnabled(true);
  m_window.setActive(true); 
  m_font.loadFromMemory(m_fontAsset->data(), m_fontAsset->size());
  m_boundingRectangle.setOutlineColor(sf::Color::Black);
  m_boundingRectangle.setOutlineThickness(1);
  m_boundingRectangle.setPosition(0, 0);  
}

void AbstractGame::run()
{
  ::sf::Clock clock;
  while (m_window.isOpen())
  {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
      switch(event.type)
      {
        case sf::Event::Closed:
          _close();
          break;
        case sf::Event::Resized:
          resize(event);
          break;
        case sf::Event::KeyPressed:
          _keyPress(event);
          break;
        case sf::Event::MouseButtonPressed:
          mousePress(event);
          break;
        case sf::Event::MouseMoved:
          mouseMoved(event);
          break;
      }
    }
    ::sf::Time elapsed = clock.restart();
    updateGame(elapsed);
    _display();
  } 
} 

void AbstractGame::_close()
{
  close();
  m_window.close();
} 

void AbstractGame::_display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  m_window.clear(sf::Color::White);
  m_window.draw(m_boundingRectangle);
  display();
  m_window.display(); 
}

void AbstractGame::resize(const sf::Event& event)
{
  glViewport(0, 0, event.size.width, event.size.height);
}

void AbstractGame::_keyPress(const ::sf::Event& event)
{
  if (event.key.code == ::sf::Keyboard::Escape) 
    _close();
  else
    keyPress(event);
} 

void AbstractGame::removeUnusedTextures()
{
  for (auto texture = m_textureMap.begin(); texture != m_textureMap.end();)
  {
    auto it = std::find_if(m_elements.begin(), m_elements.end(),
        [&texture](const ElementPtr& element) -> bool {
        return element->usesTexture(texture->second);
        });
    if (it == m_elements.end())
      texture = m_textureMap.erase(texture);
    else
      texture++;
  }
}

void AbstractGame::placeElement(
    const Resource& resource,
    const ::sf::IntRect& rectangle)
{
  auto intersected = std::find_if(m_elements.begin(), m_elements.end(), 
      [&rectangle](const ElementPtr& element) -> bool {
      return element->rectangle().intersects(rectangle);
      });            
  if (intersected == m_elements.end())
    loadElement(resource, rectangle);
}

void AbstractGame::deleteElementAtPosition(const ::sf::Vector2f& position)
{
  auto intersected = std::find_if(m_elements.begin(), m_elements.end(), 
      [&position](const ElementPtr& element) -> bool {
      return element->rectangle().contains(position.x, position.y);
      });             
  if (intersected != m_elements.end()) 
  {
    m_elements.erase(intersected);
    removeUnusedTextures();
  } 
}

std::unique_ptr<Element> AbstractGame::createGameElement(
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

void AbstractGame::loadElement(const Resource& resource,
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
      auto asset = m_fileSystem.getAsset(texture);
      newTexture->loadFromMemory(asset->data(), asset->size());
      m_textureMap.insert(std::make_pair(texture, newTexture));
      textures.push_back(newTexture);
    }
  } 
  m_elements.insert(createGameElement(resource, 
        std::move(textures), position));
}

void AbstractGame::reload(unsigned int levelNr)
{
  m_textureMap.clear();
  m_elements.clear();
  Level level(m_fileSystem, levelNr);
  std::map<const char *, TexturePtr, CompareString> textureMap;
  for (auto element : level.elements())
  {
    assert(element.resource < resources.size());
    const Resource& resource = resources[element.resource];
    loadElement(resource, ::sf::IntRect(element.x, element.y, 
          element.width, element.height));
  }
} 

void AbstractGame::display()
{
  for(auto& element : m_elements)
    element->draw(m_window);
}

} // namespace bigmama
