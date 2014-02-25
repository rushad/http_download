#include "asio_transport.h"

#include <boost/asio/connect.hpp>

namespace HttpDownload
{
  AsioTransport::AsioTransport()
    : Socket(IO)
  {
  }

  void AsioTransport::Connect(const std::string& hostName, const int port)
  {
    try
    {
      boost::asio::ip::tcp::resolver resolver(IO);
      boost::asio::ip::tcp::resolver::query query(hostName, "http");
      boost::asio::ip::tcp::resolver::iterator eps = resolver.resolve(query);
      boost::asio::connect(Socket, eps);
    }
    catch (boost::system::system_error e)
    {
      throw std::exception(e.what());
    }
/*
    const char* q = 
      "GET / HTTP/1.1\r\n"
      "Host: example.com\r\n"
      "\r\n";
    Socket.write_some(boost::asio::buffer(q, strlen(q)));

    for (;;)
    {
      char buf[128];
      boost::system::error_code error;

      size_t len = Socket.read_some(boost::asio::buffer(buf, sizeof(buf)), error);
      
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.

      std::cout.write(buf, len);
    }
*/
  }

  void AsioTransport::Write(const std::string& data)
  {
    try
    {
      Socket.write_some(boost::asio::buffer(data.c_str(), data.size()));
    }
    catch (boost::system::system_error e)
    {
      throw std::exception(e.what());
    }
  }
}