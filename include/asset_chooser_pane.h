#ifndef BIGMAMA_ASSET_CHOOSER_PANE_H
#define BIGMAMA_ASSET_CHOOSER_PANE_H

#include <QOpenGLWidget>

namespace bigmama
{

class AssetChooserPane : public QOpenGLWidget
{
  Q_OBJECT

public:
  AssetChooserPane(QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent *event) override;
};

}

#endif // BIGMAMA_ASSET_CHOOSER_PANE_H
