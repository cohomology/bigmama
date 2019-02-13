#include "game.h"
#include "assets.h"
#include "level.h"
#include "screen.h"

#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    bigmama::Screen screen;
    bigmama::AssetLibrary assets(argv[0]);
    bigmama::Game game(assets, screen);
    game.run();
  }
  catch(const std::exception& exc)
  {
    std::cerr << exc.what() << std::endl;
    exit(-1);
  }
  return 0;
}
