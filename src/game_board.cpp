#include "game_board.h"
#include "file_system.h"
#include "resources.h"

#include <QPainter>

namespace bigmama
{

GameBoard::GameBoard(FileSystem& fileSystem, QWidget *parent)
  : QOpenGLWidget(parent), m_fileSystem(fileSystem)
{ 
  setAutoFillBackground(false);
  setContentsMargins(-1, -1, -1, 0); 
  reload(0);
}

void GameBoard::paintEvent(QPaintEvent *event)
{
  glViewport(0, 0, width(), height());
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);

  for (auto& element : m_elements)
    element->draw(painter);
  painter.end();  
}

void GameBoard::reload(unsigned int levelNr)
{
  Level level(m_fileSystem, levelNr); 
  reload(level);
} 

void GameBoard::reload(const boost::filesystem::path& file)
{
  Level level(m_fileSystem, file);
  reload(level);
}

void GameBoard::reload(const Level& level)
{
  m_textureMap.clear();
  m_elements.clear();
  for (auto element : level.elements())
  {
    assert(element.resource < resources.size());
    const Resource& resource = resources[element.resource];
    loadElement(resource, QRect(element.x, element.y, 
          element.width, element.height));
  } 
} 

void GameBoard::loadElement(const Resource& resource,
                            const QRect& position)
{
  std::vector<Element::TexturePtr> textures;
  textures.reserve(resource.textures().size()); 
  for (auto& texture : resource.textures())
  {
    auto it = m_textureMap.find(texture);
    if (it != m_textureMap.end())
      textures.push_back(it->second);
    else
    {
      auto newTexture = std::make_shared<QImage>(); 
      auto asset = m_fileSystem.getAsset(texture);
      bool result = newTexture->loadFromData(
          reinterpret_cast<const uchar*>(asset->data()), 
          asset->size());
      assert(result);
      m_textureMap.insert(std::make_pair(texture, newTexture));
      textures.push_back(newTexture);
    }
  } 
  m_elements.insert(createGameElement(resource, 
        std::move(textures), position));
} 

std::unique_ptr<Element> GameBoard::createGameElement(
    const Resource& resource,
    std::vector<Element::TexturePtr>&& textures,
    const QRect& rectangle)
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

bool GameBoard::deleteElementAtPosition(const QVector2D& position)
{
  bool deleted = false;
  auto intersected = std::find_if(m_elements.begin(), m_elements.end(), 
      [&position](const Element::ElementPtr& element) -> bool {
      return element->rectangle().contains(position.x(), position.y());
      });             
  if (intersected != m_elements.end()) 
  {
    m_elements.erase(intersected);
    removeUnusedTextures();
    deleted = true;
  } 
  return deleted;
} 

bool GameBoard::placeElement(
    const Resource& resource,
    const QRect& rectangle)
{
  bool placed = false;
  auto intersected = std::find_if(m_elements.begin(), m_elements.end(), 
      [&rectangle](const Element::ElementPtr& element) -> bool {
      return element->rectangle().intersects(rectangle);
      });            
  if (intersected == m_elements.end())
  {
    loadElement(resource, rectangle);
    placed = true;
  }
  return placed;
} 

void GameBoard::removeUnusedTextures()
{
  for (auto texture = m_textureMap.begin(); texture != m_textureMap.end();)
  {
    auto it = std::find_if(m_elements.begin(), m_elements.end(),
        [&texture](const Element::ElementPtr& element) -> bool {
        return element->usesTexture(texture->second);
        });
    if (it == m_elements.end())
      texture = m_textureMap.erase(texture);
    else
      texture++;
  }
} 

}
