#include "level_editor.h"
#include "file_system.h"
#include "translation_scope.h"
#include "game_board.h"

#include <iostream>
#include <QApplication>

class BigMamaLevelApplication final : public QApplication
{
public:
  BigMamaLevelApplication(int &argc, char **& argv)
    : QApplication(argc, argv)
  { }
  bool notify(QObject* receiver, QEvent* event) override 
  {
    try 
    {
      return QApplication::notify(receiver, event);
    } 
    catch (const std::exception& ex) 
    {
      qFatal(ex.what());
    } 
    return false;
  } 
};

int main(int argc, char ** argv)
{
  using namespace bigmama;
  try
  {
    auto application 
      = std::make_unique<BigMamaLevelApplication>(argc, argv);
    bigmama::FileSystem fileSystem(argv[0]);
    TranslationScope translations(*application, fileSystem);
    LevelEditor levelEditor(fileSystem);
    //levelEditor.setWindowState(Qt::WindowFullScreen);
    levelEditor.raise();
    levelEditor.activateWindow();
    levelEditor.show();
    return application->exec();
  }
  catch(const std::exception& exception)
  {
    std::cerr << exception.what() << std::endl;
    exit(-1);
  }
  return 0;
}
