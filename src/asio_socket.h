#pragma once

#include "socket.h"

#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>

namespace HttpDownload
{
  class AsioSocket : public Socket
  {
  public:
    AsioSocket(boost::asio::io_service& io);
    virtual ~AsioSocket();

//    virtual void Connect(Endpoint ep);
    virtual void Write(const std::string& buf);
    virtual bool Read(std::string& buf, size_t& size);
    virtual void Close();

  private:
    boost::asio::ip::tcp::socket Obj;
  };
}