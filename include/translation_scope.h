#ifndef BIGMAMA_TRANSLATION_SCOPE_H
#define BIGMAMA_TRANSLATION_SCOPE_H 

#include "file_system.h"

#include <QTranslator>
#include <memory>

QT_FORWARD_DECLARE_CLASS(QApplication)

namespace bigmama
{


class TranslationScope
{
public:
  TranslationScope(
      QApplication& application,
      FileSystem& fileSystem);
private:
  std::unique_ptr<Asset> loadTranslation(); 
  std::unique_ptr<Asset> loadTranslation(const QString& lang);

  QApplication&          m_application;
  FileSystem&            m_fileSystem;
  std::unique_ptr<Asset> m_asset;
  QTranslator            m_translator;
};

}

#endif 
