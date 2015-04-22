#pragma once

#include <string>
#include <algorithm>
#include <memory>
#include "CharBuffer.h"
#include "BufferUnderflowException.h"

namespace utils {

template<typename Base, typename T>
bool instance_of(const T* obj) {
  return dynamic_cast<const Base *>(obj) != nullptr;
}

template<typename Base, typename T>
bool instance_of(std::shared_ptr<T> obj) {
  return dynamic_cast<const Base *>(obj.get()) != nullptr;
}

std::string& remove_leading_whitespace(std::string& str);
std::string& remove_trailing_whitespace(std::string& str);
std::string& trim(std::string& str);

}