#pragma once

//#include "endpoint.h"

#include <boost/shared_ptr.hpp>

#include <string>

namespace Network
{
  class Socket
  {
  public:
    virtual ~Socket()
    {
    }

//    virtual void Connect(const Endpoint& ep) = 0;
    virtual void Connect(const std::string& host, const unsigned port) = 0;
    virtual void Write(const std::string& buf) = 0;
    virtual bool Read(std::string& buf, size_t size) = 0;
    virtual void Close() = 0;

    typedef boost::shared_ptr<Socket> Ptr;
  };
}