#ifndef BIGMAMATEXTURE_H
#define BIGMAMATEXTURE_H

#include <memory>

#include <SFML/Graphics/Texture.hpp>

namespace bigmama
{

class Asset;

class Texture
{
public:
  Texture(std::unique_ptr<const Asset> asset);

  const ::sf::Texture& texture() const
  { return m_texture; }

  ::sf::Texture& texture() 
  { return m_texture; }

private:
  std::unique_ptr<const Asset> m_asset;
  ::sf::Texture                m_texture;
};

typedef std::shared_ptr<const Texture> TexturePtr;  

} // namespace bigmama

#endif // BIGMAMATEXTURE_H
