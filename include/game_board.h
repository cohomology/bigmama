#ifndef BIGMAMA_GAME_BOARD_H
#define BIGMAMA_GAME_BOARD_H

#include "element.h"
#include "level.h"

#include <QOpenGLWidget>
#include <QImage>
#include <QVector2D>

#include <cstring>
#include <set>

namespace bigmama
{

class FileSystem;

struct CompareString
{
  bool operator()(const char * first, const char * second) const
  { return std::strcmp(first, second) < 0; }
}; 

struct CompareElements
{
  bool operator()(const Element::ElementPtr& first, 
      const Element::ElementPtr& second) const
  {
    auto& fRect = first->rectangle();
    auto& sRect = second->rectangle();
    return fRect.top() < sRect.top() ||
      (fRect.top() == sRect.top() &&
       fRect.left() < sRect.left()); 
  }
}; 

class GameBoard : public QOpenGLWidget
{
  Q_OBJECT

  typedef std::map<const char *, Element::TexturePtr, CompareString> TextureMap;
  typedef std::set<Element::ElementPtr, CompareElements> ElementSet; 

public:
  GameBoard(FileSystem& fileSystem, QWidget *parent = nullptr);

protected:
  void paintEvent(QPaintEvent * event) override;

private:
  void reload(unsigned int levelNr);
  void reload(const boost::filesystem::path& path);
  void reload(const Level& level); 
  void loadElement(const Resource& resource,
                   const QRect& position); 
  std::unique_ptr<Element> createGameElement(
    const Resource& resource,
    std::vector<Element::TexturePtr>&& textures,
    const QRect& rectangle); 
  bool placeElement(
      const Resource& resource,
      const QRect& rectangle); 
  bool deleteElementAtPosition(
      const QVector2D& position);   
  void removeUnusedTextures(); 

  FileSystem& m_fileSystem;
  TextureMap m_textureMap; 
  ElementSet m_elements; 
};

}

#endif // BIGMAMA_GAME_BOARD_H
