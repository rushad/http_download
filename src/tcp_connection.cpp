#include "tcp_connection.h"

#include <boost/system/system_error.hpp>

namespace Network
{
  TcpConnection::TcpConnection(Socket::Ptr sock)
    : Sock(sock)
    , Connected(false)
  {
  }
//    void Connect(Endpoint ep);
  void TcpConnection::Connect(const std::string& host, const unsigned port)
  {
    try
    {
      Sock->Connect(host, port);
    }
    catch (boost::system::system_error e)
    {
      throw Exception(e.what());
    }
    Connected = true;
  }

  void TcpConnection::Write(const std::string& data)
  {
    if (!Connected)
      throw std::exception("Socket is not connected");

    Sock->Write(data);
  }

  bool TcpConnection::IsConnected() const
  {
    return Connected;
  }

}