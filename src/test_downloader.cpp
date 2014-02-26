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
        , Connections(0)
      {
      }

      virtual void Connect(const std::string& hostName, const int port)
      {
        if (hostName != "example.com")
          throw std::exception("Wrong host name");
        if (port != 80)
          throw std::exception("Wrong port");
        Connected = true;
        ++Connections;
      }

      virtual void Write(const std::string& data)
      {
        Wrote += data;
      }

      virtual std::string Read()
      {
        return "HTTP/1.1 200 OK\r\n";
      }

      virtual void Close()
      {
        Connected = false;
      }

    public:
      bool Connected;
      unsigned Connections;
      std::string Wrote;
    };

    class TestDownloader : public ::testing::Test
    {
    };

    TEST_F(TestDownloader, CheckParseUrlFull)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("http://example.com:123/path", proto, host, port, path);
      EXPECT_EQ("http", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestDownloader, CheckParseUrlWithoutProto)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("example.com:123/path", proto, host, port, path);
      EXPECT_EQ("", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestDownloader, CheckParseUrlWithoutHost)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("http://:123/path", proto, host, port, path);
      EXPECT_EQ("http", proto);
      EXPECT_EQ("", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestDownloader, CheckParseUrlWithoutHostAndPort)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("http:///path", proto, host, port, path);
      EXPECT_EQ("http", proto);
      EXPECT_EQ("", host);
      EXPECT_EQ(80, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestDownloader, CheckParseUrlWithoutPort)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("http://example.com/path", proto, host, port, path);
      EXPECT_EQ("http", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(80, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestDownloader, CheckParseUrlWithoutPath)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("http://example.com:123", proto, host, port, path);
      EXPECT_EQ("http", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/", path);
    }

    TEST_F(TestDownloader, CheckParseUrlWithoutPortAndPath)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      std::string proto, host, path;
      int port;
      downloader.ParseUrl("http://example.com/", proto, host, port, path);
      EXPECT_EQ("http", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(80, port);
      EXPECT_EQ("/", path);
    }

    TEST_F(TestDownloader, DownloadShouldConnect)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      downloader.Download("http://example.com");
      EXPECT_EQ(1, transport.Connections);
    }

    TEST_F(TestDownloader, DownloadShouldThrowOnWrongHostName)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      EXPECT_THROW(downloader.Download("http://wrongexample.com"), std::exception);
    }

    TEST_F(TestDownloader, DownloadShouldThrowOnWrongPort)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      EXPECT_THROW(downloader.Download("http://example.com:81"), std::exception);
    }

    TEST_F(TestDownloader, DownloadShouldWrite)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      downloader.Download("http://example.com");
      EXPECT_NE("", transport.Wrote);
   }

    TEST_F(TestDownloader, DownloadShouldCloseSocket)
    {
      FakeTransport transport;
      Downloader downloader(transport);
      downloader.Download("http://example.com");
      EXPECT_FALSE(transport.Connected);
    }
  }
}