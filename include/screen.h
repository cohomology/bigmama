#ifndef BIGMAMASCREEN_H
#define BIGMAMASCREEN_H

namespace bigmama
{

class Screen
{
public:
  unsigned int width() const
  { return m_width; }

  unsigned int height() const
  { return m_height; }

  unsigned int statusAreaHeight() const
  { return m_statusAreaHeight; }

private:
  static const int m_width = 1920;
  static const int m_height = 1080;
  static const int m_statusAreaHeight = 120;
};

}

#endif // BIGMAMASCREEN_H 
