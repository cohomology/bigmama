#ifndef BIGMAMASCREEN_H
#define BIGMAMASCREEN_H

namespace bigmama
{

class Screen
{
public:
  unsigned int width() const
  { return screenWidth; }

  unsigned int height() const
  { return screenHeight; }

  unsigned int minLeftBorder() const
  { return leftBorder; }

  unsigned int minTopBorder() const
  { return topBorder; }

private:
  static const int screenWidth = 1920;
  static const int screenHeight = 1080;
  static const int leftBorder = 50;
  static const int topBorder = 50;   
};

}

#endif // BIGMAMASCREEN_H 
