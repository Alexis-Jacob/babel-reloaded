#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <vector>
#include <string>

namespace Utils
{

  std::vector<char>	stringToChar(std::string oOBstr);
  std::vector<char>	cryptPassword(std::vector<char> &&password);
  std::vector<char>	stringToPassword(std::string &str);
};

#endif
