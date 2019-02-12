#include "game.h"
#include "assets.h"
#include "level.h"
#include "state.h"

#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    bigmama::AssetLibrary assets(argv[0]);
    bigmama::State state(assets);
    bigmama::Game game(assets, state);
    game.run();
  }
  catch(const std::exception& exc)
  {
    std::cerr << exc.what() << std::endl;
    exit(-1);
  }
  return 0;
}
