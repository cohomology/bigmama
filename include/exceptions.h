#include <QException> 
#include <QCoreApplication> 

namespace bigmama
{

class AssetNotFound : public QException
{
  Q_DECLARE_TR_FUNCTIONS(AssetNotFound)
public:
  AssetNotFound(const char * asset)
    : m_msg(QString(tr("Error: Could not find asset: ")) + "\"" + asset + "\"")
  { }

  const char * what() const throw() override
  { return m_msg.toUtf8(); }

private:
  QString m_msg;
}; 

class FileNotFound : public QException
{
  Q_DECLARE_TR_FUNCTIONS(FileNotFound) 
public:
  FileNotFound(const char * fileName)
    : m_msg(QString(tr("Error: Could not open file: ")) +"\"" + fileName + "\"")
  { }

  const char * what() const throw() override
  { 
    return m_msg.toUtf8(); 
  }

private:
  QString m_msg;
}; 

class JsonParseError : public QException
{
public:
  JsonParseError(const QString& msg)
    : m_msg(msg)
  { }

  const char * what() const throw() override
  { 
    return m_msg.toUtf8(); 
  }

private:
  QString m_msg;
}; 

}
