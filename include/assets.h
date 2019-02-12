#ifndef BIGMAMAASSETS_H
#define BIGMAMAASSETS_H

#include <vector>
#include <string>
#include <memory>

namespace bigmama
{

class AssetNotFound : public std::exception
{
public:
  AssetNotFound(const char * asset)
    : m_msg(std::string("Error: Could not find asset: \"") + asset + "\"")
  { }

  const char * what() const throw() override
  { 
    return m_msg.c_str(); 
  }

private:
  std::string m_msg;
};

class Asset
{
  friend class AssetLibrary;
public:
  Asset(const std::vector<char>&) = delete;
  Asset(std::vector<char>&& data)
    : m_data(std::move(data))
  { } 
  Asset(Asset&&) = default;
  Asset(const Asset&) = default;

  const void * data() const
  { return &m_data[0]; }

  std::size_t size() const
  { return m_data.size(); }

private:
  const std::vector<char> m_data;
}; 

class AssetLibrary
{
public:
  AssetLibrary(const char * calledProgram);
  ~AssetLibrary();
  std::unique_ptr<Asset> get(const char * asset) const;
  std::unique_ptr<Asset> get(const std::string& asset) const
  { return this->get(asset.c_str()); }
}; 

} // namespace bigmama

#endif // BIGMAMAASSETS_H
