#pragma once

#include <string>

namespace HttpDownload
{
  class Transport
  {
  public:
    virtual ~Transport()
    {
    }
    virtual void Connect(const std::string& hostname, const int port) = 0;
    virtual void Write(const std::string& data) = 0;
    virtual std::string Read() = 0;
    virtual void Close() = 0;
  };
}