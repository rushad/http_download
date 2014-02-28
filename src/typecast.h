#pragma once

#include <sstream>
#include <string>

namespace Typecast
{
  unsigned HexToUint(const std::string& hex);
  std::string UintToString(const unsigned num);
}