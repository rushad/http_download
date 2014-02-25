#pragma once

#include "transport.h"

#include <string>

namespace HttpDownload
{
  class Downloader
  {
  public:
    Downloader(Transport& trans);
    void Connect(const std::string& hostName, const int port);
    void Write(const std::string& data);

  private:
    Transport& Trans;
  };
}