#include "game_board.h"
#include "file_system.h"

#include <QPainter>

namespace bigmama
{

GameBoard::GameBoard(FileSystem& fileSystem, QWidget *parent)
  : QOpenGLWidget(parent)
{ 
  setAutoFillBackground(false);
  setContentsMargins(-1, -1, -1, 0); 
  auto asset = fileSystem.getAsset("level_edit_frame.png");
  m_image = QImage::fromData(
      reinterpret_cast<const uchar*>(asset->data()), 
      asset->size());
}

void GameBoard::paintEvent(QPaintEvent *event)
{
  glViewport(0, 0, width(), height());
  glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.drawImage(50, 50, m_image);
  painter.end();  
}

}
