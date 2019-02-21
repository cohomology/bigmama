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
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setPen(Qt::red);
  QRect rect = QRect(geometry());
  painter.drawRect(rect);
  painter.end(); 
} 

}
