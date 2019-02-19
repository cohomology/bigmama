#include "level_editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  using namespace bigmama;

  QApplication application(argc, argv);
  LevelEditor levelEditor;
  levelEditor.setWindowState(Qt::WindowFullScreen);
  levelEditor.raise();
  levelEditor.activateWindow();
  levelEditor.show();
  return application.exec();
}
