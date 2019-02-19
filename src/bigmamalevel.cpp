#include "level_editor.h"
#include "file_system.h"
#include "level.h"
#include "screen.h"

#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    bigmama::Screen screen;
    bigmama::FileSystem assets(argv[0]);
    bigmama::LevelEditor levelEditor(assets, screen);
    levelEditor.run();
  }
  catch(const std::exception& exc)
  {
    std::cerr << exc.what() << std::endl;
    exit(-1);
  }
  return 0;
}
