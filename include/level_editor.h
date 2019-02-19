#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>

namespace bigmama
{

class LevelEditor : public QMainWindow
{
  Q_OBJECT

public:
  LevelEditor(QWidget *parent = nullptr);
  ~LevelEditor() override;
  void keyPressEvent(QKeyEvent * event) override;
};

}

#endif // LEVELEDITOR_H
