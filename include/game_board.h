#ifndef BIGMAMA_GAME_BOARD_H
#define BIGMAMA_GAME_BOARD_H

#include <QOpenGLWidget>

namespace bigmama
{

class GameBoard : public QOpenGLWidget
{
  Q_OBJECT
public:
  GameBoard(QWidget *parent = nullptr);

protected:
  void initializeGL() override;
  void resizeGL(int width, int height) override;
  void paintGL() override;

private:
};

}

#endif // BIGMAMA_GAME_BOARD_H
