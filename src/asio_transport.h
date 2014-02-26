#pragma once

#include "transport.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <string>

namespace HttpDownload
{
  class AsioTransport : public Transport
  {
  public:
    AsioTransport();
    virtual ~AsioTransport();
    virtual void Connect(const std::string& hostName, const int port);
    virtual void Write(const std::string& data);
    virtual std::string Read();
    virtual void Close();

  private:
    boost::asio::io_service IO;
    boost::asio::ip::tcp::socket Socket;
  };
}