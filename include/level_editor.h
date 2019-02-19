#ifndef LEVELEDITOR_H
#define LEVELEDITOR_H

#include <QMainWindow>

class LevelEditor : public QMainWindow
{
  Q_OBJECT

public:
  LevelEditor(QWidget *parent = nullptr);
  ~LevelEditor() override;
};

#endif // LEVELEDITOR_H
