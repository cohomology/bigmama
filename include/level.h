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

class TextureIterator
  : public boost::iterator_facade<
        TextureIterator
      , TexturePtr
      , boost::forward_traversal_tag
      , TexturePtr
    >, public JsonIterator
{
public:
  TextureIterator()
    : JsonIterator()
  { }

  TextureIterator(
    const AssetLibrary&   library, 
    const ::Json::Value&  value) 
    : JsonIterator(library, value)
  { }

private:
  friend class boost::iterator_core_access;
  TexturePtr dereference() const;
};  

class TextureView
{
  friend class Level;
public:
  TextureIterator begin();
  TextureIterator end()
  { return TextureIterator(); } 
private:
  TextureView(const AssetLibrary& library, 
              ::Json::Value       root)            
    : m_library(library), m_root(root)
  { }

  const AssetLibrary& m_library; 
  ::Json::Value  m_root; 
};

struct Wall
{
  unsigned int texture;
  unsigned int x;
  unsigned int y;
  unsigned int width;
  unsigned int height;
};

class WallIterator
  : public boost::iterator_facade<
        WallIterator
      , Wall
      , boost::forward_traversal_tag
      , Wall
    >, public JsonIterator
{
public:
  WallIterator()
    : JsonIterator()
  { }

  WallIterator(
    const AssetLibrary&   library, 
    const ::Json::Value&  value) 
    : JsonIterator(library, value)
  { }

private:
  friend class boost::iterator_core_access;
  Wall dereference() const;
};  

class WallView
{
  friend class Level;
public:
  WallIterator begin();
  WallIterator end()
  { return WallIterator(); } 
private:
  WallView(const AssetLibrary& library, 
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

  TextureView textures() const
  { return TextureView(m_library, m_root); }

  WallView walls() const
  { return WallView(m_library, m_root); } 

private:
  const AssetLibrary& m_library;
  ::Json::Reader m_reader;
  ::Json::Value  m_root;
};

} // namespace bigmama

#endif // BIGMAMALEVEL_H
