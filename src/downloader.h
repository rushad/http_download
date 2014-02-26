#pragma once

#include "transport.h"

#include <string>

namespace HttpDownload
{
  class Downloader
  {
  public:
    Downloader(Transport& trans);
    std::string Download(const std::string& url);
    void ParseUrl(const std::string& url, std::string& proto, std::string& host, int& port, std::string& path);

  private:
    Transport& Trans;
  };
}