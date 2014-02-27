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

  private:
    Transport& Trans;
  };
}