#include "assets.h"

#include <physfs.h>
#include <cassert>

namespace bigmama
{

#include "bigmama.pak.cpp"   

AssetLibrary::AssetLibrary(const char * calledProgram)
{
  PHYSFS_init(calledProgram);   
  int result = PHYSFS_mountMemory(assetData, sizeof(assetData), nullptr,
                                  ".pak", nullptr, 0);
  assert(result != 0);
}

AssetLibrary::~AssetLibrary()
{
  PHYSFS_deinit(); 
}

Asset AssetLibrary::get(const char * asset) const
{
  if (!PHYSFS_exists(asset))
    throw AssetNotFound(asset);
  PHYSFS_file* assetFile = PHYSFS_openRead(asset);
  std::vector<char> data(PHYSFS_fileLength(assetFile));
  PHYSFS_readBytes (assetFile, &data[0], PHYSFS_fileLength(assetFile));
  return Asset(std::move(data));
}

};
