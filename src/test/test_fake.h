#pragma once

#include "../factory.h"
#include "../socket.h"

#include <boost/asio/error.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/system_error.hpp>

namespace Network
{
  namespace Test
  {
    class FakeSocket : public Socket
    {
    public:
      FakeSocket()
        : Connected(false)
      {
      }

  //    virtual void Connect(Endpoint ep);
      virtual void Connect(const std::string& host, const unsigned port)
      {
        if (host != "example.com")
          throw boost::system::system_error(boost::asio::error::host_not_found);
        Connected = true;
      }

      virtual void Write(const std::string& buf)
      {
        Wrote += buf;
      }

      virtual bool Read(std::string& buf, size_t size)
      {
        return true;
      }

      virtual void Close()
      {
      }

      typedef boost::shared_ptr<FakeSocket> Ptr;

      bool Connected;
      std::string Wrote;
    };

    class FakeFactory : public Factory
    {
    public:
      virtual ~FakeFactory()
      {
      }

      virtual Socket::Ptr CreateSocket()
      {
        return Socket::Ptr(new FakeSocket());
      }
    };
  }
}