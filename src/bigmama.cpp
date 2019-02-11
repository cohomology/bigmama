#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
  AssetLibrary assets(argv[0]);
  Game game(assets);
  game.run();
  return 0;
}
