#pragma once

#include "url.h"

#include <string>

namespace HttpDownload
{
  class Url::Internal
  {
  public:
    Internal(const std::string& urlString);

    size_t GetProto(std::string& proto);
    size_t GetHostPort(const size_t startPos, std::string& host_port);
    static void SplitHostPort(const std::string& host_port, std::string& host, unsigned& port);
    void GetPath(const size_t startPos, std::string& path);
    void Parse(std::string& proto, std::string& host, unsigned& port, std::string& path);

  private:
    std::string UrlString;
  };
}