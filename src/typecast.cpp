#include "typecast.h"

namespace Typecast
{
  unsigned HexToUint(const std::string& hex)
  {
    unsigned ch;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> ch;
    return ch;
  }

  std::string UintToString(const unsigned num)
  {
    std::stringstream ss;
    ss << std::dec << num;
    return ss.str();
  }
}