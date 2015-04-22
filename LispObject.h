#pragma once

#include <exception>

namespace solisp {

class LispObject {
public:
  virtual ~LispObject() = 0;
};

class InvalidLispObject : public std::exception {};

}
