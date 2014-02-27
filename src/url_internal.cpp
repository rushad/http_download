#include "url_internal.h"

namespace HttpDownload
{
  Url::Internal::Internal(const std::string &urlString)
    : UrlString(urlString)
  {
  }

  size_t Url::Internal::GetProto(std::string& proto)
  {
    size_t endPos = UrlString.find("://");
    if (endPos == std::string::npos)
    {
      proto = "";
      return 0;
    }
    proto = UrlString.substr(0, endPos);
    return endPos + 3;
  }

  size_t Url::Internal::GetHostPort(const size_t startPos, std::string& hostPort)
  {
    size_t endPos = UrlString.find("/", startPos);
    if (endPos == std::string::npos)
    {
      endPos = UrlString.size();
    }
    hostPort = UrlString.substr(startPos, endPos - startPos);
    return endPos;
  }

  void Url::Internal::SplitHostPort(const std::string& hostPort, std::string& host, unsigned& port)
  {
    size_t delimPos = hostPort.find(":");
    if (delimPos == std::string::npos)
    {
      host = hostPort;
      port = HTTP_PORT;
    }
    else
    {
      host = hostPort.substr(0, delimPos);
      port = atoi(hostPort.substr(delimPos + 1).c_str());
    }
  }

  void Url::Internal::GetPath(const size_t startPos, std::string& path)
  {
    std::string p = UrlString.substr(startPos);
    if (p.empty())
      p = "/";
    path = p;
  }

  void Url::Internal::Parse(std::string& proto, std::string& host, unsigned& port, std::string& path)
  {
    size_t hostPortPos = GetProto(proto);
    std::string hostPort;
    size_t pathPos = GetHostPort(hostPortPos, hostPort);
    SplitHostPort(hostPort, host, port);
    GetPath(pathPos, path);
  }
}