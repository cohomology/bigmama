#ifndef BIGMAMALEVEL_H
#define BIGMAMALEVEL_H

#include <jsoncpp/json/json.h>

namespace bigmama
{

class AssetLibrary;

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
