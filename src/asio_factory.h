#pragma once

#include "factory.h"
#include "socket.h"

#include <boost/asio/io_service.hpp>

namespace Network
{
  class AsioFactory : public Factory
  {
  public:
    virtual ~AsioFactory()
    {
    }

    virtual Socket::Ptr CreateSocket();

  private:
    boost::asio::io_service IO;

  };
}