#include "downloader.h"

namespace HttpDownload
{
  Downloader::Downloader(Transport& trans)
    : Trans(trans)
  {
  }

  std::string Downloader::Download(const std::string& url)
  {
    std::string proto, host, path;
    int port;

    ParseUrl(url, proto, host, port, path);

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

  void Downloader::ParseUrl(const std::string& url, std::string& proto, std::string& host, int& port, std::string& path)
  {
    size_t hostBeginPos = 0;
    size_t protoSuffixPos = url.find("://");
    if (protoSuffixPos != std::string::npos)
    {
      hostBeginPos = protoSuffixPos + 3;
      proto = url.substr(0, protoSuffixPos);
    }
    else
    {
      proto = "";
    }

    size_t portPrefixPos = url.find(":", hostBeginPos);
    size_t hostSuffixPos = url.find("/", hostBeginPos);
    if (portPrefixPos != std::string::npos)
    {
      hostSuffixPos = portPrefixPos;
    }
    if (hostSuffixPos == std::string::npos)
    {
      hostSuffixPos = url.size();
    }
    host = url.substr(hostBeginPos, hostSuffixPos - hostBeginPos);

    size_t pathPrefixPos = std::string::npos;
    if (portPrefixPos == std::string::npos)
    {
      port = 80;
      pathPrefixPos = hostSuffixPos;
    }
    else
    {
      size_t portSuffixPos = url.find("/", portPrefixPos + 1);
      if (portSuffixPos == std::string::npos)
      {
        portSuffixPos = url.size();
      }
      port = atoi(url.substr(portPrefixPos + 1, portSuffixPos - portPrefixPos - 1).c_str());
      pathPrefixPos = portSuffixPos;
    }

    if (pathPrefixPos == url.size())
    {
      path = "/";
    }
    else
    {
      path = url.substr(pathPrefixPos);
    }
  }

}