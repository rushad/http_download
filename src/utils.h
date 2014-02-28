#pragma once

#include <sstream>
#include <string>

namespace Utils
{
  unsigned HexToUint(const std::string& hex);
  std::string UintToString(const unsigned num);
}