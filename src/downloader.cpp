#include "downloader.h"

namespace HttpDownload
{
  Downloader::Downloader(Transport& trans)
    : Trans(trans)
  {
  }

  void Downloader::Connect(const std::string& hostName, const int port)
  {
    Trans.Connect(hostName, port);
  }

  void Downloader::Write(const std::string& data)
  {
    Trans.Write(data);
  }

}