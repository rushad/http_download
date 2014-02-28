#pragma once

#include "socket.h"

namespace Network
{
  class Factory
  {
  public:
    virtual ~Factory()
    {
    }

    virtual Socket::Ptr CreateSocket() = 0;
  };
}