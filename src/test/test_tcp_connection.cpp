#include "test_fake.h"
#include "../tcp_connection.h"

#include <gtest/gtest.h>

namespace Network
{
  namespace Test
  {
    class TestTcpConnection : public ::testing::Test
    {
    public:
      TestTcpConnection()
        : Sock(new FakeSocket())
        , Tcp(Sock)
      {
      }

      FakeSocket::Ptr Sock;
      TcpConnection Tcp;
    };

    TEST_F(TestTcpConnection, CheckConnect)
    {
      Tcp.Connect("example.com", 80);

      EXPECT_TRUE(Sock->Connected);
      EXPECT_TRUE(Tcp.IsConnected());
    }

    TEST_F(TestTcpConnection, ConnectShouldThrowOnWrongHostName)
    {
      EXPECT_THROW(Tcp.Connect("wrong.host.name", 80), TcpConnection::Exception);
    }

    TEST_F(TestTcpConnection, WriteShouldThrowIfNotConnected)
    {
      EXPECT_THROW(Tcp.Write("GET"), std::exception);
    }

    TEST_F(TestTcpConnection, WriteShouldWrite)
    {
      const std::string testString = "test";
      Tcp.Connect("example.com", 80);

      Tcp.Write(testString);

      EXPECT_EQ(testString, Sock->Wrote);
    }
  }
}