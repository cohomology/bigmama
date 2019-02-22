#include "asset_chooser_pane.h"

#include <QPainter>
#include <QPushButton>

namespace bigmama
{

AssetChooserPane::AssetChooserPane(QWidget *parent)
    : QWidget(parent)
{
  setContentsMargins(-1, 0, -1, -1);
  
  QPalette pal = palette();

  // set black background
  pal.setColor(QPalette::Background, Qt::black);
  setAutoFillBackground(true);
  setPalette(pal);
}


}
