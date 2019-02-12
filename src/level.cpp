#include "level.h"
#include "assets.h"
#include "state.h"

#include <boost/lexical_cast.hpp>

namespace bigmama
{

Level::Level(const AssetLibrary& library,
             unsigned int level)
  : m_reader(), m_root()
{
  std::string levelFile("level");
  levelFile.append(boost::lexical_cast<std::string>(level));
  levelFile.append(".json");
  Asset asset = library.get(levelFile);
  const char * data = reinterpret_cast<const char*>(asset.data());
  m_reader.parse(data, data + asset.size(), m_root);
}

}
