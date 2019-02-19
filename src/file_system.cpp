#include "file_system.h"

#include <physfs.h>
#include <cassert>

namespace bigmama
{

#include "bigmama.pak.cpp"   

FileSystem::FileSystem(const char * calledProgram)
{
  PHYSFS_init(calledProgram);   
  int result = PHYSFS_mountMemory(assetData, sizeof(assetData), nullptr,
                                  ".pak", nullptr, 0);
  assert(result != 0);
}

FileSystem::~FileSystem()
{
  PHYSFS_deinit(); 
}

std::unique_ptr<Asset> FileSystem::getAsset(const char * asset) const
{
  if (!PHYSFS_exists(asset))
    throw AssetNotFound(asset);
  PHYSFS_file* assetFile = PHYSFS_openRead(asset);
  std::vector<char> data(PHYSFS_fileLength(assetFile));
  PHYSFS_readBytes (assetFile, &data[0], PHYSFS_fileLength(assetFile));
  return std::make_unique<Asset>(std::move(data));
}

};
