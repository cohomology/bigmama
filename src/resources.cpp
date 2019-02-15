#include "resources.h"

namespace bigmama
{

const std::vector<Resource> resources = {
  { 
    Resource(
        ResourceKind::Wall, 
        { "stone_grey.png" },
        "Grey stone",
        ElementClassKind::SimpleElement),
    Resource(
        ResourceKind::Wall, 
        { "stone_red.png" },
        "Red stone",
        ElementClassKind::SimpleElement) 
  }
};

}
