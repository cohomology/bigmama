#include "asset_chooser_pane.h"

#include <QPainter>

namespace bigmama
{

AssetChooserPane::AssetChooserPane(QWidget *parent)
    : QOpenGLWidget(parent)
{
  setContentsMargins(-1, 0, -1, -1);
}

void AssetChooserPane::paintEvent(QPaintEvent *event)
{
  glViewport(0, 0, width(), height());
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
} 

}
