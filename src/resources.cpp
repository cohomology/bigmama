#include "resources.h"

namespace bigmama
{

#define BIGMAMA_RESOURCE(kind, assets, description, elementClass) \
  Resource( ResourceKind::kind, assets, description, ElementClassKind::elementClass)

const std::vector<Resource> resources = {
  {
    BIGMAMA_RESOURCE(Wall,    { "stone_brick1.png" }, "Brick stone",      SimpleElement),
    BIGMAMA_RESOURCE(Wall,    { "stone_brick2.png" }, "Brick stone",      SimpleElement),   
    BIGMAMA_RESOURCE(Monster, { "skull.png" },        "Skull (Monster)",  SimpleElement),    
    BIGMAMA_RESOURCE(Item,    { "coin.png" },         "Coin",             SimpleElement),     
  }
};

}
