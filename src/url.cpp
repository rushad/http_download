#include "url.h"

#include <boost/lexical_cast.hpp>

#include <algorithm>

namespace Internet
{
  Url::Url(const std::string &url)
  {
    size_t hostPortPos = ParseProto(url, Proto);
    std::transform(Proto.begin(), Proto.end(), Proto.begin(), ::tolower);

    std::string hostPort;
    size_t pathPos = ParseHostPort(url, hostPortPos, hostPort);
    SplitHostPort(hostPort, Host, Port);
    std::transform(Host.begin(), Host.end(), Host.begin(), ::tolower);

    std::string path;
    ParsePath(url, pathPos, path);
    Path = Unescape(path);
  }

  std::string Url::GetProto() const
  {
    return Proto;
  }

  std::string Url::GetHost() const
  {
    return Host;
  }

  unsigned Url::GetPort() const
  {
    return Port;
  }

  std::string Url::GetPath() const
  {
    return Path;
  }

  size_t Url::ParseProto(const std::string& url, std::string& proto)
  {
    size_t endPos = url.find("://");
    if (endPos == std::string::npos)
    {
      proto = "";
      return 0;
    }
    proto = url.substr(0, endPos);
    return endPos + 3;
  }

  size_t Url::ParseHostPort(const std::string& url, const size_t startPos, std::string& hostPort)
  {
    size_t endPos = url.find("/", startPos);
    if (endPos == std::string::npos)
    {
      endPos = url.size();
    }
    hostPort = url.substr(startPos, endPos - startPos);
    return endPos;
  }

  void Url::SplitHostPort(const std::string& hostPort, std::string& host, unsigned& port)
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

  void Url::ParsePath(const std::string& url, const size_t startPos, std::string& path)
  {
    std::string p = url.substr(startPos);
    if (p.empty())
      p = "/";
    path = p;
  }

  std::string Url::Unescape(const std::string& url)
  {
    std::string res;
    std::string::const_iterator it, end;

    for (it = url.begin(), end = url.end(); it != end; ++it)
    {
      if (*it == '%')
      {
        std::string hex;
        hex += *(++it);
        hex += *(++it);

        int ch;
        std::stringstream ss;
        ss << std::hex << hex;
        ss >> ch;

        res += ch;
      }
      else
      {
        res += *it;
      }
    }

    return res;
  }

}