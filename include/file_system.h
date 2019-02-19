#ifndef BIGMAMA_ASSETS_H
#define BIGMAMA_ASSETS_H

#include "exceptions.h"

#include <vector>
#include <string>
#include <memory>

namespace bigmama
{

class Asset
{
  friend class FileSystem;
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

class FileSystem
{
public:
  FileSystem(const char * calledProgram);
  ~FileSystem();
  std::unique_ptr<Asset> getAsset(const char * asset) const;
  std::unique_ptr<Asset> getAsset(const std::string& asset) const
  { return this->getAsset(asset.c_str()); }
  const char * getPrefDir() const;
}; 

} // namespace bigmama

#endif // BIGMAMA_ASSETS_H
