#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class MainWindow
{
public:
  MainWindow() 
    : m_settings(16, 8, 8, 3, 0), m_mode(1920, 1080), 
    m_window(m_mode, "bigmama", sf::Style::Fullscreen, m_settings)
  {
    m_window.setVerticalSyncEnabled(true);
    m_window.setActive(true);
  }

  void run()
  {
    while (m_window.isOpen())
    {
      sf::Event event;
      while (m_window.pollEvent(event))
      {
        switch(event.type)
        {
          case sf::Event::Closed:
            close();
            break;
          case sf::Event::Resized:
            resize(event);
            break;
          case sf::Event::KeyPressed:
            keypress(event);
            break;
        }
      }
      display();
    } 
  }

protected:

  void close()
  {
    m_window.close();
  }

  void display()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_window.clear(sf::Color::White);
    m_window.display(); 
  }

  void resize(const sf::Event& event)
  {
    glViewport(0, 0, event.size.width, event.size.height);
  }

  void keypress(const sf::Event& event)
  {
    switch(event.key.code)
    {
      case sf::Keyboard::Escape:
        close();
        break;
      default:
        break;
    }
  }

private:
  sf::ContextSettings m_settings;
  sf::VideoMode       m_mode;
  sf::RenderWindow    m_window;
};

int main(int argc, char *argv[])
{
  MainWindow main;
  main.run();
  return 0;
}
