#include "translation_scope.h"
#include "file_system.h"

#include <QApplication>

namespace bigmama
{

TranslationScope::TranslationScope(
    QApplication& application,
    FileSystem& fileSystem) :
  m_application(application),
  m_fileSystem(fileSystem),
  m_asset(),
  m_translator()
{
  m_asset = loadTranslation();
  if (m_asset && 
        m_translator.load(
          reinterpret_cast<const unsigned char*>(
            m_asset->data()), m_asset->size()))
  {
    m_application.installTranslator(&m_translator);
  }
}

std::unique_ptr<Asset> TranslationScope::loadTranslation()
{
  QString defaultLocale = QLocale::system().name(); 
  defaultLocale.truncate(defaultLocale.lastIndexOf("_")); 
  auto translationFile = loadTranslation(defaultLocale);
  if (!translationFile)
    translationFile = loadTranslation("en");
  return translationFile;
}

std::unique_ptr<Asset> TranslationScope::loadTranslation(const QString& lang) 
{
  std::unique_ptr<Asset> translationFile;
  try
  {
    translationFile = m_fileSystem.getAsset(
        (QString("bigmama_") + lang + ".qm").toUtf8());
  }
  catch(const std::exception&)
  { }
  return translationFile;
}

}
