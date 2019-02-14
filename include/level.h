#ifndef BIGMAMALEVEL_H
#define BIGMAMALEVEL_H

#include "types.h"

#include <jsoncpp/json/json.h>
#include <boost/iterator/iterator_facade.hpp>

namespace bigmama
{

class AssetLibrary;

class JsonIterator
{
public:
  JsonIterator()
    :  m_library(nullptr), m_value(nullptr),
    m_counter(0)
  { }

  explicit JsonIterator(
    const AssetLibrary&   library, 
    const ::Json::Value&  value) 
    : m_library(&library), m_value(&value),
    m_counter(0)
  { }

protected:
  friend class boost::iterator_core_access;

  void increment(); 

  bool equal(const JsonIterator & other) const;

  const AssetLibrary * m_library; 
  const ::Json::Value * m_value;
  unsigned int m_counter;
}; 

struct ElementDescriptor
{
  unsigned int resource;
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
};

class ElementIterator
  : public boost::iterator_facade<
        ElementIterator
      , ElementDescriptor
      , boost::forward_traversal_tag
      , ElementDescriptor
    >, public JsonIterator
{
public:
  ElementIterator()
    : JsonIterator()
  { }

  ElementIterator(
    const AssetLibrary&   library, 
    const ::Json::Value&  value) 
    : JsonIterator(library, value)
  { }

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
  ElementView(const AssetLibrary& library, 
           ::Json::Value       root)            
    : m_library(library), m_root(root)
  { }

  const AssetLibrary& m_library; 
  ::Json::Value  m_root; 
}; 

class Level
{
public:
  Level(const AssetLibrary& library,
        unsigned int levelNr);

  ElementView elements() const
  { return ElementView(m_library, m_root); } 

private:
  std::string generateLevelFileName(unsigned int levelNr);
  void loadLevelEditTemplate();
  void loadFromFile(std::ifstream& stream); 
  void loadLevel(unsigned int levelNr); 
  void loadLevelFromAssets(const std::string& levelFile); 

  const AssetLibrary& m_library;
  ::Json::Reader m_reader;
  ::Json::Value  m_root;
};

} // namespace bigmama

#endif // BIGMAMALEVEL_H
