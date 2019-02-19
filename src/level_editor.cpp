#include "level_editor.h"

#include <QKeyEvent>
#include <QApplication>

namespace bigmama
{

LevelEditor::LevelEditor(QWidget *parent)
    : QMainWindow(parent)
{
}

LevelEditor::~LevelEditor()
{

}

void LevelEditor::keyPressEvent(QKeyEvent * event) 
{
  switch(event->key())
  {
    case ::Qt::Key::Key_Escape:
      QApplication::quit();
      break;
    default:
      break;
  }
}

}
