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

  std::string AsioTransport::Read()
  {
    std::string res;
    try
    {
      while (true)
      {
        char buf[4096];
        boost::system::error_code error;

        size_t len = Socket.read_some(boost::asio::buffer(buf, sizeof(buf)), error);
        
        if (error)
        {
          if (error == boost::asio::error::eof)
          {
            break;
          }
          else
          {
            throw boost::system::system_error(error);
          }
        }

        res += std::string(buf, len);
      }
    }
    catch (boost::system::system_error e)
    {
      throw std::exception(e.what());
    }
    return res;
  }

  void AsioTransport::Close()
  {
    try
    {
      Socket.close();
    }
    catch (boost::system::system_error e)
    {
      throw std::exception(e.what());
    }
  }

}