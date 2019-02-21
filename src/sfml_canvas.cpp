#include "sfml_canvas.h"

namespace bigmama
{

SFMLCanvas::SFMLCanvas(QWidget *parent) : 
  QWidget(parent), m_timer(), m_initialized (false)
{
  setAttribute(Qt::WA_PaintOnScreen);
  setAttribute(Qt::WA_OpaquePaintEvent);
  setAttribute(Qt::WA_NoSystemBackground);

  setFocusPolicy(Qt::StrongFocus);

  ::sf::RenderWindow::setSize(::sf::Vector2u(QWidget::width(), 
        QWidget::height())); 

  m_timer.setInterval(0);
}

QPaintEngine *SFMLCanvas::paintEngine() const
{
  return nullptr;
}

void SFMLCanvas::paintEvent(QPaintEvent *)
{
  onUpdate();
  ::sf::RenderWindow::display();
}

void SFMLCanvas::resizeEvent(QResizeEvent *event)
{
  ::sf::RenderWindow::setSize(sf::Vector2u(QWidget::width(), 
        QWidget::height()));
}

void SFMLCanvas::showEvent(QShowEvent *)
{
  if (!m_initialized)
  {
    // Under X11, we need to flush the commands sent to the server to ensure that
    // SFML will get an updated view of the windows
#ifdef Q_WS_X11
    XFlush(QX11Info::display());
#endif
    ::sf::RenderWindow::create(static_cast<::sf::WindowHandle>(winId()));   
    onInit();
    // Setup the timer to trigger a refresh at specified framerate
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(repaint()));
    m_timer.start();
    m_initialized = true;
  }
}

}
