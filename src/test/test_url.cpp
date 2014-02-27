#include "../url_internal.h"

#include <gtest/gtest.h>

namespace HttpDownload
{
  namespace Test
  {
    class TestUrlInternal : public ::testing::Test
    {
    };

    TEST_F(TestUrlInternal, CheckGetProto)
    {
      Url::Internal url("http://example.com");
      std::string proto;

      size_t protoEndPos = url.GetProto(proto);

      EXPECT_EQ("http", proto);
      EXPECT_EQ(7, protoEndPos);
    }

    TEST_F(TestUrlInternal, CheckGetProtoWithoutProto)
    {
      Url::Internal url("example.com");
      std::string proto;

      size_t protoEndPos = url.GetProto(proto);

      EXPECT_EQ("", proto);
      EXPECT_EQ(0, protoEndPos);
    }

    TEST_F(TestUrlInternal, CheckGetHostPort)
    {
      Url::Internal url("http://example.com:123");
      std::string proto, host_port;

      size_t hostBeginPos = url.GetProto(proto);
      size_t pathBeginPos = url.GetHostPort(hostBeginPos, host_port);

      EXPECT_EQ("example.com:123", host_port);
      EXPECT_EQ(22, pathBeginPos);
    }

    TEST_F(TestUrlInternal, CheckSplitHostPort)
    {
      std::string host;
      unsigned port;

      Url::Internal::SplitHostPort("example.com:123", host, port);

      EXPECT_EQ("example.com", host);
      EXPECT_EQ(123, port);
    }

    TEST_F(TestUrlInternal, CheckSplitHostPortWithoutPort)
    {
      std::string host;
      unsigned port;

      Url::Internal::SplitHostPort("example.com", host, port);

      EXPECT_EQ("example.com", host);
      EXPECT_EQ(80, port);
    }

    TEST_F(TestUrlInternal, CheckGetPathWithPath)
    {
      Url::Internal url("http://example.com:123/path");
      std::string path;

      url.GetPath(22, path);

      EXPECT_EQ("/path", path);
    }

    TEST_F(TestUrlInternal, CheckGetPathWithoutPath)
    {
      Url::Internal url("http://example.com");
      std::string path;

      url.GetPath(18, path);

      EXPECT_EQ("/", path);
    }

    TEST_F(TestUrlInternal, CheckParseFull)
    {
      Url::Internal url("http://example.com:123/path");
      std::string proto, host, path;
      unsigned port;

      url.Parse(proto, host, port, path);

      EXPECT_EQ("http", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestUrlInternal, CheckParseWithoutProto)
    {
      Url::Internal url("example.com:123/path");
      std::string proto, host, path;
      unsigned port;

      url.Parse(proto, host, port, path);

      EXPECT_EQ("", proto);
      EXPECT_EQ("example.com", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestUrlInternal, CheckParseWithoutHost)
    {
      Url::Internal url("http://:123/path");
      std::string proto, host, path;
      unsigned port;

      url.Parse(proto, host, port, path);

      EXPECT_EQ("http", proto);
      EXPECT_EQ("", host);
      EXPECT_EQ(123, port);
      EXPECT_EQ("/path", path);
    }

    TEST_F(TestUrlInternal, CheckParseWithoutHostAndPort)
    {
      Url::Internal url("http:///path");
      std::string proto, host, path;
      unsigned port;

      url.Parse(proto, host, port, path);

      EXPECT_EQ("http", proto);
      EXPECT_EQ("", host);
      EXPECT_EQ(80, port);
      EXPECT_EQ("/path", path);
    }
/*
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
*/
  }
}