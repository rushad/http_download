#pragma once

#include "socket.h"

namespace Network
{
  class TcpConnection
  {
  public:
    TcpConnection(Socket::Ptr sock);
//    void Connect(Endpoint ep);
    void Connect(const std::string& host, const unsigned port);
    void Write(const std::string& data);
    bool IsConnected() const;

    class Exception
    {
    public:
      Exception(const std::string& what)
        : Desc(what)
      {
      }
      std::string What() const
      {
        return Desc;
      }

    private:
      std::string Desc;
    };

  private:
    Socket::Ptr Sock;
    bool Connected;
  };
}