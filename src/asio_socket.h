#pragma once

#include "socket.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace Network
{
  class AsioSocket : public Socket
  {
  public:
    AsioSocket(boost::asio::io_service& io);
    virtual ~AsioSocket();

//    virtual void Connect(const Endpoint& ep);
    virtual void Connect(const std::string& host, const unsigned port);
    virtual void Write(const std::string& buf);
    virtual bool Read(std::string& buf, size_t size);
    virtual void Close();

  private:
    boost::asio::io_service& IO;
    boost::asio::ip::tcp::socket Obj;
  };
}