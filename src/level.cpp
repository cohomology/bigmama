#include "level.h"
#include "file_system.h"

#include <boost/lexical_cast.hpp>
#include <cassert>
#include <fstream>
#include <streambuf>

#include <QFile>
#include <QJsonObject>
#include <QFileInfo>

namespace bigmama
{

ElementDescriptor ElementIterator::dereference() const
{
  const QJsonArray::const_iterator it 
    = this->base_reference();
  const QJsonValue& element = *it;
  return ElementDescriptor {
    element["resource"].toInt(),
    element["x"].toInt(),
    element["y"].toInt(),
    element["width"].toInt(),
    element["height"].toInt()
  };
} 

ElementIterator ElementView::begin() 
{
  return ElementIterator(m_root["elements"].toArray().begin());
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
  loadLevelFromAssets("template.json");
}

void Level::loadFromFile(const char * fileName)
{
  QFile file(fileName);
  QByteArray blob = file.readAll();
  QJsonParseError error;
  m_document = QJsonDocument::fromJson(blob, &error);
  if (error.error != QJsonParseError::NoError)
    throw JsonParseError(error.errorString()); 
  m_root = m_document.object();
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
  auto asset = m_library.getAsset(levelFile);
  const char * data = reinterpret_cast<const char*>(asset->data());
  QByteArray blob(data, asset->size());
  QJsonParseError error; 
  m_document = QJsonDocument::fromJson(blob, &error);
  if (error.error != QJsonParseError::NoError)
    throw JsonParseError(error.errorString());
  m_root = m_document.object(); 
}

Level::Level(const FileSystem& library,
             unsigned int levelNr)
  : m_library(library), m_document(), m_root()
{
  if (levelNr == 0)
    loadLevelEditTemplate();
  else 
    loadLevel(levelNr);
}

Level::Level(const FileSystem& library,
             const ::boost::filesystem::path& path) 
  : m_library(library), m_document(), m_root()
{
  const char * fileName = path.c_str();
  QFileInfo checkFile(fileName);
  if (checkFile.exists() && checkFile.isFile() &&
        checkFile.isReadable())
    loadFromFile(fileName);
  else
    throw FileNotFound(fileName);
}

}
