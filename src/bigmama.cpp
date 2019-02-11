#include "game.h"
#include "assets.h"

int main(int argc, char *argv[])
{
  bigmama::AssetLibrary assets(argv[0]);
  bigmama::Game game(assets);
  game.run();
  return 0;
}
