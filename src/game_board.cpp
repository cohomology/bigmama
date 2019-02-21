#include "game_board.h"

#include <QPainter>

namespace bigmama
{

GameBoard::GameBoard(QWidget *parent)
    : QOpenGLWidget(parent)
{
  setContentsMargins(-1, -1, -1, 0);
  QSurfaceFormat format;
  format.setVersion(4, 5); // or anything >= 3.2
  format.setProfile(QSurfaceFormat::CoreProfile);
  setFormat(format);
}

void GameBoard::initializeGL() 
{
  glClearColor(255, 255, 255, 1);
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
}

void GameBoard::resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);
}

void GameBoard::paintGL() 
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  painter.fillRect(geometry(), ::Qt::red);
}

}
