#pragma once

#include <boost/noncopyable.hpp>

#include <memory>
#include <string>

namespace HttpDownload
{
  class Url : public boost::noncopyable
  {
  public:
    class Internal;
    static const unsigned HTTP_PORT = 80;

    Url(const std::string& urlString);
    ~Url();

    void Parse(std::string& proto, std::string& host, unsigned& port, std::string& path);

  private:
//    std::auto_ptr<Internal> UrlObj;
    Internal* Obj;
  };
}