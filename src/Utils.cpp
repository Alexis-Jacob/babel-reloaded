#include "Utils.hpp"

namespace Utils
{
  std::vector<char>	stringToChar(std::string str)
  {
    std::vector<char>	rep(str.begin(), str.end());
    return rep;
  }
  
  
  std::vector<char>	cryptPassword(std::vector<char> &&password)
  {
    // static const char _key = 56; //crypt password 
    // for (char &c : password)
    //   c = c ^ _key; 
    return (std::move(password));
  }
  
  std::vector<char>	stringToPassword(std::string &str)
  {
    return std::move(cryptPassword(stringToChar(str)));
  }
}
