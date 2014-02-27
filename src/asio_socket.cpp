#include "asio_socket.h"

#include <boost/scoped_array.hpp>

namespace HttpDownload
{
  AsioSocket::AsioSocket(boost::asio::io_service& io)
    : Obj(io)
  {
  }
    
  AsioSocket::~AsioSocket()
  {
    try
    {
      Close();
    }
    catch (boost::system::system_error)
    {
    }
  }

/*  void AsioSocket::Connect(const Endpoint& ep)
  {
    const AsioEndpoint epAsio = static_cast<AsioEndpoint>(ep);
    boost::asio::connect(Obj, epAsio.GetEndpointIterator());
  }*/

  void AsioSocket::Write(const std::string& buf)
  {
    Obj.write_some(boost::asio::buffer(buf.c_str(), buf.size()));
  }

  bool AsioSocket::Read(std::string& buf, size_t& size)
  {
    boost::system::error_code error;
    boost::scoped_array<char> rawBuf(new char[size]);

    size_t read = Obj.read_some(boost::asio::buffer(rawBuf.get(), size), error);

    if (error && error != boost::asio::error::eof)
      throw boost::system::system_error(error);

    buf = std::string(rawBuf.get(), read);
    size = read;

    return (error != boost::asio::error::eof);
  }

  void AsioSocket::Close()
  {
    Obj.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    Obj.close();
  }
}