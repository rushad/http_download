#pragma once

//#include "endpoint.h"

#include <string>

namespace HttpDownload
{
  class Socket
  {
  public:
    virtual ~Socket()
    {
    }

//    virtual void Connect(Endpoint ep) = 0;
    virtual void Write(const std::string& buf) = 0;
    virtual bool Read(std::string& buf, size_t& size) = 0;
    virtual void Close() = 0;
  };
}