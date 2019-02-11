#include "physfs.h"

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
