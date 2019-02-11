#include "assets.h"

#include <physfs.h>

#include "bigmama.pak.cpp"

namespace bigmama
{

AssetLibrary::AssetLibrary(const char * calledProgram)
{
  PHYSFS_init(calledProgram);   
}

AssetLibrary::~AssetLibrary()
{
  PHYSFS_deinit(); 
}

};
