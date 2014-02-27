#pragma once

#include <string>

namespace Internet
{
  static const unsigned HTTP_PORT = 80;

  class Url
  {
  public:
    Url(const std::string& urlString);
    std::string GetProto() const;
    std::string GetHost() const;
    unsigned GetPort() const;
    std::string GetPath() const;

  private:
    static size_t ParseProto(const std::string& url, std::string& proto);
    static size_t ParseHostPort(const std::string& url, const size_t startPos, std::string& host_port);
    static void SplitHostPort(const std::string& host_port, std::string& host, unsigned& port);
    static void ParsePath(const std::string& url, const size_t startPos, std::string& path);

    std::string Proto;
    std::string Host;
    unsigned Port;
    std::string Path;
  };
}