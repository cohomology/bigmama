#ifndef BIGMAMATYPES_H
#define BIGMAMATYPES_H

#include <memory>
#include <SFML/Graphics/Texture.hpp>

namespace bigmama
{

typedef std::shared_ptr<const ::sf::Texture> TexturePtr; 

class TextureProvider
{
public:
  virtual TexturePtr texture(const char * textureName) = 0;
}; 

} // namespace bigmama

#endif // BIGMAMASTATE_H 
