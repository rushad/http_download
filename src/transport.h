#pragma once

#include <string>

namespace HttpDownload
{
  class Transport
  {
  public:
    virtual void Connect(const std::string& hostname, const int port) = 0;
    virtual void Write(const std::string& data) = 0;
  };
}