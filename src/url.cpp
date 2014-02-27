#include "url.h"
#include "url_internal.h"

namespace HttpDownload
{
  Url::Url(const std::string& urlString)
    : Obj(new Url::Internal(urlString))
  {
  }

  Url::~Url()
  {
    delete Obj;
  }

  void Url::Parse(std::string& proto, std::string& host, unsigned& port, std::string& path)
  {
    Obj->Parse(proto, host, port, path);
  }
}