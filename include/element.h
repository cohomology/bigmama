#ifndef BIGMAMASTATE_H
#define BIGMAMASTATE_H

#include <QRect> 
#include <QImage>
#include <vector>
#include <memory>

QT_FORWARD_DECLARE_CLASS(QPainter) 

namespace bigmama
{

class FileSystem;
class Screen;
class Resource;

class Element
{
public:
  typedef std::shared_ptr<QImage> TexturePtr;
  typedef std::shared_ptr<Element> ElementPtr;

  Element(const Resource& resource,
          std::vector<TexturePtr>&& textures, 
          const QRect& rectangle); 
  Element(const Resource& resource,
          std::initializer_list<TexturePtr>&& textures,
          const QRect& rectangle);

  const Resource& resource() const 
  { return m_resource; }

  virtual void draw(QPainter& painter) = 0; 
  const QRect& rectangle() 
  { return m_rectangle; }
  const std::vector<TexturePtr>& textures() const
  { return m_textures; }
  std::shared_ptr<QImage> sprite() 
  { return m_sprite; }
  bool usesTexture(const TexturePtr& ptr) const
  {
    return std::find(m_textures.begin(), m_textures.end(),
        ptr) != m_textures.end();
  }
protected:
  const Resource&                m_resource;
  const std::vector<TexturePtr>  m_textures;
  std::shared_ptr<QImage>        m_sprite;
  QRect                          m_rectangle; 
  unsigned int                   m_currentTexture;
};

class SimpleElement : public Element
{
public:
  SimpleElement(const Resource& resource,
                Element::TexturePtr&& textures, 
                const QRect& rectangle);  

  void draw(QPainter& painter) override;
};

}

#endif // BIGMAMASTATE_H
