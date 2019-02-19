#ifndef BIGMAMAABSTRACTGAME_H
#define BIGMAMAABSTRACTGAME_H 

#include "types.h"
#include "element.h"
#include "screen.h"
#include "file_system.h"

#include <SFML/Graphics.hpp>
#include <cstring>  
#include <set>

namespace bigmama
{ 

struct CompareString
{
  bool operator()(const char * first, const char * second) const
  { return std::strcmp(first, second) < 0; }
}; 

struct CompareElements
{
  bool operator()(const ElementPtr& first, 
      const ElementPtr& second) const
  {
    auto& fRect = first->rectangle();
    auto& sRect = second->rectangle();
    return fRect.top < sRect.top ||
      (fRect.top == sRect.top &&
       fRect.left < sRect.left); 
  }
};

class AbstractGame
{
  typedef std::map<const char *, 
    TexturePtr, CompareString> TextureMap;
  typedef std::set<ElementPtr,
    CompareElements> ElementSet;
public:
  AbstractGame(const FileSystem& library,
               const Screen& screen,
               const char * executable);
  void run();

protected:
  virtual void display();
  virtual void mousePress(const ::sf::Event& event) { }
  virtual void mouseMoved(const ::sf::Event& event) { }
  virtual void keyPress(const ::sf::Event& event) { }
  virtual void updateGame(const ::sf::Time& time) { }
  virtual void reload(unsigned int levelNr);
  virtual void close() { }

  std::unique_ptr<Element> createGameElement(
      const Resource& resource,
      std::vector<TexturePtr>&& textures,
      const ::sf::IntRect& rectangle);  
  template<typename T>
  bool isInsideStatusArea(const ::sf::Vector2<T>& position)
  { return position.y >= m_screen.height() - m_screen.statusAreaHeight(); }
  template<typename T>
  bool isInsideGameArea(const ::sf::Vector2<T>& position)
  { return !isInsideStatusArea(position); }
  void placeElement(
      const Resource& resource,
      const ::sf::IntRect& rectangle); 
  void deleteElementAtPosition(const ::sf::Vector2f& position);  

  ::sf::RenderWindow& window() 
  { return m_window; }
  const ElementSet& elements() const
  { return m_elements; }

private:
  void _close();
  void _display();
  void resize(const ::sf::Event& event);
  void _keyPress(const ::sf::Event& event);

  void removeUnusedTextures(); 
  void loadElement(const Resource& resource,
                   const ::sf::IntRect& position);   

private:
  ::sf::ContextSettings        m_settings;
  ::sf::VideoMode              m_mode;
  ::sf::RenderWindow           m_window;

  const FileSystem&            m_fileSystem;
  const Screen&                m_screen; 
  TextureMap                   m_textureMap; 
  ElementSet                   m_elements;
 
  std::unique_ptr<Asset>       m_fontAsset;
  ::sf::Font                   m_font; 

  ::sf::RectangleShape         m_boundingRectangle;   
}; // class AbstractGame

} // namespace bigmama 

#endif // BIGMAMAABSTRACTGAME_H 
