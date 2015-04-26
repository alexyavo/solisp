#pragma once

#include <string>
#include <algorithm>
#include <memory>
#include "CharBuffer.h"
#include "BufferUnderflowException.h"

namespace utils {

template<typename DynamicType, typename StaticType>
bool instance_of(const StaticType* obj) {
  return dynamic_cast<const DynamicType *>(obj) != nullptr;
}

template<typename DynamicType, typename StaticType>
bool instance_of(std::shared_ptr<StaticType> obj) {
  return std::dynamic_pointer_cast<const DynamicType>(obj) != nullptr;
}

std::string& remove_leading_whitespace(std::string& str);
std::string& remove_trailing_whitespace(std::string& str);
std::string& trim(std::string& str);

}