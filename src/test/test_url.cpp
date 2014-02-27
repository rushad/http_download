#include "../url.h"

#include <gtest/gtest.h>

namespace Internet
{
  namespace Test
  {
    class TestUrl : public ::testing::Test
    {
    };

    TEST_F(TestUrl, CheckFullNormalizedURL)
    {
      Url url("http://example.com:123/path");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("example.com", url.GetHost());
      EXPECT_EQ(123, url.GetPort());
      EXPECT_EQ("/path", url.GetPath());
    }

    TEST_F(TestUrl, CheckFullNotNormalizedURL)
    {
      Url url("HTTP://Example.COM:123/Path");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("example.com", url.GetHost());
      EXPECT_EQ(123, url.GetPort());
      EXPECT_EQ("/Path", url.GetPath());
    }

    TEST_F(TestUrl, CheckWithoutProto)
    {
      Url url("example.com:123/path");
      EXPECT_EQ("", url.GetProto());
      EXPECT_EQ("example.com", url.GetHost());
      EXPECT_EQ(123, url.GetPort());
      EXPECT_EQ("/path", url.GetPath());
    }

    TEST_F(TestUrl, CheckParseWithoutHost)
    {
      Url url("http://:123/path");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("", url.GetHost());
      EXPECT_EQ(123, url.GetPort());
      EXPECT_EQ("/path", url.GetPath());
    }

    TEST_F(TestUrl, CheckParseWithoutHostAndPort)
    {
      Url url("http:///path");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("", url.GetHost());
      EXPECT_EQ(80, url.GetPort());
      EXPECT_EQ("/path", url.GetPath());
    }

    TEST_F(TestUrl, CheckParseUrlWithoutPort)
    {
      Url url("http://example.com/path");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("example.com", url.GetHost());
      EXPECT_EQ(80, url.GetPort());
      EXPECT_EQ("/path", url.GetPath());
    }

    TEST_F(TestUrl, CheckParseUrlWithoutPath)
    {
      Url url("http://example.com:123");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("example.com", url.GetHost());
      EXPECT_EQ(123, url.GetPort());
      EXPECT_EQ("/", url.GetPath());
    }

    TEST_F(TestUrl, CheckParseUrlWithoutPortAndPath)
    {
      Url url("http://example.com/");
      EXPECT_EQ("http", url.GetProto());
      EXPECT_EQ("example.com", url.GetHost());
      EXPECT_EQ(80, url.GetPort());
      EXPECT_EQ("/", url.GetPath());
    }
  }
}