#include "asio_transport.h"
#include "downloader.h"

#include <gtest/gtest.h>

#include <iostream>

bool CheckOptions(int argc, char** argv)
{
  for (int i = 1; i < argc; ++i)
  {
    std::string opt(argv[i]);
    if(opt == "--gtest")
    {
      std::cout << "Running tests..." << std::endl;
      testing::InitGoogleTest(&argc, argv);
      RUN_ALL_TESTS();
      return false;
    }
  }

  return true;
}


int main(int argc, char* argv[])
{
  setlocale(LC_ALL, "RUS");

  if(!CheckOptions(argc, argv))
  {
    return -1;
  }

  try
  {
    HttpDownload::AsioTransport trans;
    HttpDownload::Downloader downloader(trans);
    std::cout << downloader.Download("http://example.com:80/") << std::endl;
  }
  catch (std::exception e)
  {
    std::cout << e.what() << std::endl;
  }

  return 0;
}