#include "game.h"
#include "assets.h"
#include "level.h"

#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    bigmama::AssetLibrary assets(argv[0]);
    bigmama::Level level(assets, 1);
    bigmama::Game game(assets);
    game.run();
  }
  catch(const std::exception& exc)
  {
    std::cerr << exc.what() << std::endl;
    exit(-1);
  }
  return 0;
}
