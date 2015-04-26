#pragma once

#include <exception>
#include <ostream>

namespace solisp {

class LispObject {
public:
  virtual ~LispObject() = 0;

public:
  virtual void print(std::ostream& out) const = 0;
};

class InvalidLispObject : public std::exception {};

}
