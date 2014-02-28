#include "asio_factory.h"
#include "asio_socket.h"

namespace Network
{
  Socket::Ptr AsioFactory::CreateSocket()
  {
    return Socket::Ptr(new AsioSocket(IO));
  }
}