#include "utils.h"

namespace utils {


std::string& remove_leading_whitespace(std::string& str) {
  str.erase(str.begin(),
            std::find_if(str.begin(),
                         str.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
  return str;
}

std::string& remove_trailing_whitespace(std::string& str) {
  str.erase(std::find_if(str.rbegin(), str.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(),
            str.end());
  return str;
}

std::string& trim(std::string& str) {
  return remove_trailing_whitespace(remove_leading_whitespace(str));
}

}