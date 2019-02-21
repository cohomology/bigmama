#include <SFML/Graphics.hpp>
#include <QWidget>
#include <QTimer>

namespace bigmama
{

class SFMLCanvas : public QWidget, public ::sf::RenderWindow
{
  Q_OBJECT
public :
  SFMLCanvas(QWidget *parent); 
protected :
  virtual void onInit() {}
  virtual void onUpdate() {}
 
  QPaintEngine *paintEngine() const override;
  void showEvent(QShowEvent*) override;
  void paintEvent(QPaintEvent*) override;
  void resizeEvent(QResizeEvent *event) override; 

  QTimer m_timer;
  bool   m_initialized;
};

}
