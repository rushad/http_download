#include "downloader.h"
#include "url.h"

namespace HttpDownload
{
  Downloader::Downloader(Transport& trans)
    : Trans(trans)
  {
  }

  std::string Downloader::Download(const std::string& urlString)
  {
    std::string proto, host, path;
    unsigned port;

    Url url(urlString);
    url.Parse(proto, host, port, path);

    if (proto != "http")
      throw std::exception(("Unknown protocol: " + proto).c_str());

    Trans.Connect(host, port);

    const std::string query = 
      "GET " + path + " HTTP/1.1\r\n"
      "Host: " + host + "\r\n"
      "Connection: close\r\n"
      "\r\n";
    Trans.Write(query);

    std::string res = Trans.Read();

    Trans.Close();

    return res;
  }
}