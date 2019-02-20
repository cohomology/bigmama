#ifndef BIGMAMA_LEVEL_H
#define BIGMAMA_LEVEL_H

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/filesystem.hpp> 

#include <QJsonValue>
#include <QJsonDocument>
#include <QJsonArray>

namespace bigmama
{

class FileSystem;

struct ElementDescriptor
{
  int resource;
  int x;
  int y;
  int width;
  int height;
}; 

class ElementIterator
  : public boost::iterator_adaptor<
        ElementIterator            
      , QJsonArray::const_iterator 
      , ElementDescriptor
      , boost::forward_traversal_tag   
    >
{
private:
  struct enabler {};  

public:
  ElementIterator()
    : ElementIterator::iterator_adaptor_() {}

  explicit ElementIterator(const QJsonArray::const_iterator& it)
    : ElementIterator::iterator_adaptor_(it) {}

private:
  friend class boost::iterator_core_access;
  ElementDescriptor dereference() const;
};

class ElementView
{
  friend class Level;
public:
  ElementIterator begin();
  ElementIterator end()
  { return ElementIterator(); } 
private:
  ElementView(const FileSystem& library, 
              const QJsonValue& root)            
    : m_library(library), m_root(root)
  { }

  const FileSystem& m_library; 
  const QJsonValue& m_root; 
}; 

class Level
{
public:
  Level(const FileSystem& library,
        unsigned int levelNr);

  Level(const FileSystem& library,
        const ::boost::filesystem::path& path);

  ElementView elements() const
  { return ElementView(m_library, m_root); } 

private:
  std::string generateLevelFileName(unsigned int levelNr);
  void loadLevelEditTemplate();
  void loadFromFile(const char * fileName);
  void loadLevel(unsigned int levelNr); 
  void loadLevelFromAssets(const std::string& levelFile); 

  const FileSystem& m_library;
  QJsonDocument     m_document;
  QJsonValue        m_root;
};

} // namespace bigmama

#endif // BIGMAMA_LEVEL_H
