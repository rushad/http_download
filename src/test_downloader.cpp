#include "downloader.h"
#include "transport.h"

#include <gtest/gtest.h>

namespace HttpDownload
{
  namespace Test
  {
    class FakeTransport : public Transport
    {
    public:
      FakeTransport()
        : Connected(false)
      {
      }

      virtual void Connect(const std::string& hostName, const int port)
      {
        if (hostName != "example.com")
          throw std::exception("Wrong host name");
        if (port != 80)
          throw std::exception("Wrong port");
        Connected = true;
      }

      virtual void Write(const std::string& data)
      {
        Wrote += data;
      }

    public:
      bool Connected;
      std::string Wrote;
    };

    class TestDownloader : public ::testing::Test
    {
    };

    TEST_F(TestDownloader, ConnectShouldConnect)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      downloader.Connect("example.com", 80);
      EXPECT_TRUE(transport.Connected);
    }

    TEST_F(TestDownloader, ConnectShouldThrowOnWrongHostName)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      EXPECT_THROW(downloader.Connect("wrongexample.com", 80), std::exception);
    }

    TEST_F(TestDownloader, ConnectShouldThrowOnWrongPort)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      EXPECT_THROW(downloader.Connect("example.com", 81), std::exception);
    }

    TEST_F(TestDownloader, WriteShouldWrite)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      downloader.Connect("example.com", 80);
      downloader.Write("test");
      EXPECT_EQ("test", transport.Wrote);
   }
  }
}