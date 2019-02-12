#include "texture.h"
#include "assets.h"

namespace bigmama
{

Texture::Texture(std::unique_ptr<const Asset> asset)
  : m_asset{std::move(asset)}, m_texture{}
{
  m_texture.loadFromMemory(m_asset->data(), 
      m_asset->size()); 
}

} // namespace bigmama
