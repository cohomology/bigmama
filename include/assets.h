#ifndef BIGMAMAASSETS_H
#define BIGMAMAASSETS_H

#include <vector>
#include <string>

namespace bigmama
{

class AssetNotFound : public std::exception
{
public:
  AssetNotFound(const char * msg)
    : m_msg(msg)
  { }

  const char * what() const throw() override
  { return m_msg.c_str(); }

private:
  std::string m_msg;
};

class Asset
{
  friend class AssetLibrary;
public:
  const void * data() const
  { return &m_data[0]; }

  std::size_t size() const
  { return m_data.size(); }

private:
  Asset(std::vector<char>&& data)
    : m_data(std::move(data))
  { }

  const std::vector<char> m_data;
}; 

class AssetLibrary
{
public:
  AssetLibrary(const char * calledProgram);
  ~AssetLibrary();
  Asset get(const char * asset) const;
}; 

} // namespace bigmama

#endif // BIGMAMAASSETS_H
