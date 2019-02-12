#ifndef BIGMAMALEVEL_H
#define BIGMAMALEVEL_H

#include "types.h"
//#include "asset.h"

#include <jsoncpp/json/json.h>
#include <boost/iterator/iterator_facade.hpp>

namespace bigmama
{

class AssetLibrary;

/* class TextureIterator */
/*   : public boost::iterator_facade< */
/*         TextureIterator */
/*       , std::shared_ptr<Asset> */
/*       , boost::forward_traversal_tag */
/*       , std::shared_ptr<Asset> */
/*     > */
/* { */
/* public: */
/*   TextureIterator() */
/*     : m_asset(nullptr) {} */

/*   explicit TextureIterator(std::shared_ptr<Asset> asset) */
/*     : m_asset(asset) {} */

/* private: */
/*   friend class boost::iterator_core_access; */

/*   void increment() { m_node = m_node->next(); } */

/*   bool equal(node_iterator const& other) const */
/*   { */
/*     return */ 
/*       (m_asset == nullptr && other.m_asset == nullptr) || */
/*       (m_asset != nullptr && other.m_asset != nullptr && */
/*        *m_asset->get() == *other.m_asset->get()); */
/*   } */

/*   Asset dereference() const { return m_asset; } */

/*   const AssetLibrary&    m_library; */ 
/*   std::shared_ptr<Asset> m_asset; */
/* }; */  

class Level
{
public:
  Level(const AssetLibrary& library,
        unsigned int level);

private:
  ::Json::Reader m_reader;
  ::Json::Value  m_root;
};

} // namespace bigmama

#endif // BIGMAMALEVEL_H
