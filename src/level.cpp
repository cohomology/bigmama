#include "level.h"
#include "assets.h"

#include <boost/lexical_cast.hpp>
#include <cassert>

namespace bigmama
{

void JsonIterator::increment() 
{
  assert(m_value != nullptr);
  ++m_counter;
  if (m_counter >= m_value->size())
    m_value = nullptr;
}

bool JsonIterator::equal(const JsonIterator & other) const
{
  return 
    (m_value == nullptr && other.m_value == nullptr) ||
    (m_value != nullptr && other.m_value != nullptr &&
     *m_value == *other.m_value &&
     m_library == other.m_library &&
     m_counter == other.m_counter);
} 

TexturePtr TextureIterator::dereference() const
{
  assert(m_value != nullptr);
  assert(m_library != nullptr);
  auto asset = 
    m_library->get((*m_value)[m_counter].asString());
  auto texture = std::make_shared<::sf::Texture>();
  texture->loadFromMemory(asset->data(), asset->size());
  return texture;
} 

Wall WallIterator::dereference() const
{
  assert(m_value != nullptr);
  assert(m_library != nullptr);
  const ::Json::Value& wall = (*m_value)[m_counter];
  return Wall {
    wall["texture"].asUInt(),
    wall["x"].asUInt(),
    wall["y"].asUInt(),
    wall["width"].asUInt(),
    wall["height"].asUInt()
  };
} 

TextureIterator TextureView::begin() 
{
  const ::Json::Value& textures = m_root["textures"];
  return textures.size() == 0 ?
    TextureIterator() : 
    TextureIterator(m_library, textures);
} 

WallIterator WallView::begin() 
{
  const ::Json::Value& walls = m_root["walls"];
  return walls.size() == 0 ?
    WallIterator() : 
    WallIterator(m_library, walls);
} 

Level::Level(const AssetLibrary& library,
             unsigned int levelNr)
  : m_library(library), m_reader(), m_root()
{
  std::string levelFile("level");
  levelFile.append(boost::lexical_cast<std::string>(levelNr));
  levelFile.append(".json");
  auto asset = library.get(levelFile);
  const char * data = reinterpret_cast<const char*>(asset->data());
  m_reader.parse(data, data + asset->size(), m_root);
}

}
