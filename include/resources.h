#ifndef BIGMAMA_RESOURCES_H
#define BIGMAMA_RESOURCES_H

#include <vector>
#include <functional>
#include <memory>

namespace bigmama 
{

enum class ResourceKind
{
  Invalid = 0u,
  Wall    = 1u,
  Item    = 2u,
  Monster = 3u
};

enum class ElementClassKind
{
  InvalidElement = 0u,
  SimpleElement  = 1u
};

class Resource
{
public:
  Resource(const ResourceKind type,
           const std::initializer_list<const char *>& textures,
           const char * description,
           ElementClassKind elementClassKind)
  : m_type{type}, m_textures{textures},
  m_description{description}, m_elementClassKind{elementClassKind}
  { }

  ResourceKind type() const
  { return m_type; }

  const std::vector<const char *>& textures() const
  { return m_textures; }

  const char * description() const
  { return m_description; }

  ElementClassKind elementClassKind() const
  { return m_elementClassKind; }

private:
  ResourceKind              m_type;
  std::vector<const char *> m_textures;
  const char *              m_description;
  ElementClassKind          m_elementClassKind;
};

extern const std::vector<Resource> resources;

} // namespace bigmama

#endif // BIGMAMARESOURCES_H
