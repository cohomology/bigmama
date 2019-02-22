#ifndef BIGMAMA_ASSET_CHOOSER_PANE_H
#define BIGMAMA_ASSET_CHOOSER_PANE_H

#include <QOpenGLWidget>

namespace bigmama
{

class AssetChooserPane : public QWidget
{
  Q_OBJECT

public:
  AssetChooserPane(QWidget *parent = nullptr);
};

}

#endif // BIGMAMA_ASSET_CHOOSER_PANE_H
