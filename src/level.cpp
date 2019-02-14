#include "level.h"
#include "assets.h"

#include <boost/lexical_cast.hpp>
#include <cassert>
#include <fstream>
#include <streambuf>

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

ElementDescriptor ElementIterator::dereference() const
{
  assert(m_value != nullptr);
  assert(m_library != nullptr);
  const ::Json::Value& wall = (*m_value)[m_counter];
  return ElementDescriptor {
    wall["resource"].asUInt(),
    wall["x"].asUInt(),
    wall["y"].asUInt(),
    wall["width"].asUInt(),
    wall["height"].asUInt()
  };
} 

ElementIterator ElementView::begin() 
{
  const ::Json::Value& elements = m_root["elements"];
  return elements.size() == 0 ?
    ElementIterator() : 
    ElementIterator(m_library, elements);
} 

std::string Level::generateLevelFileName(unsigned int levelNr)
{
  std::string levelFile("level");
  if (levelNr != 0)
    levelFile.append(boost::lexical_cast<std::string>(levelNr));
  levelFile.append(".json"); 
  return levelFile;
}

void Level::loadLevelEditTemplate()
{
  std::ifstream stream("level.json");
  if (stream.good())
    loadFromFile(stream);
  else
    loadLevelFromAssets("template.json");
}

void Level::loadFromFile(std::ifstream& stream)
{
  std::string str((std::istreambuf_iterator<char>(stream)),
                   std::istreambuf_iterator<char>());
  m_reader.parse(str.c_str(), str.c_str() + str.size(), m_root);   
}

void Level::loadLevel(unsigned int levelNr)
{
  std::string levelFile("level");
  levelFile.append(boost::lexical_cast<std::string>(levelNr));
  levelFile.append(".json"); 
  loadLevelFromAssets(levelFile);
}

void Level::loadLevelFromAssets(const std::string& levelFile)
{
  auto asset = m_library.get(levelFile);
  const char * data = reinterpret_cast<const char*>(asset->data());
  m_reader.parse(data, data + asset->size(), m_root);  
}

Level::Level(const AssetLibrary& library,
             unsigned int levelNr)
  : m_library(library), m_reader(), m_root()
{
  if (levelNr == 0)
    loadLevelEditTemplate();
  else 
    loadLevel(levelNr);
}

}
