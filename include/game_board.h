#ifndef BIGMAMA_GAME_BOARD_H
#define BIGMAMA_GAME_BOARD_H

#include <QOpenGLWidget>
#include <QImage>

namespace bigmama
{

class FileSystem;

class GameBoard : public QOpenGLWidget
{
  Q_OBJECT
public:
  GameBoard(FileSystem& fileSystem, QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent * event) override;

private:
  QImage m_image;
};

}

#endif // BIGMAMA_GAME_BOARD_H
