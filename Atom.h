#pragma once

#include <string>

#include "LispObject.h"

namespace solisp {

class Atom : public LispObject {
private:
  const std::string m_str;

public:
  Atom(const std::string& str);

  bool eq(const Atom& other);

public:
  static bool is_valid_atom(const std::string& str);
};

class InvalidAtom : public InvalidLispObject {
private:
  const std::string m_atom;

public:
  InvalidAtom(const std::string& atom);

  const std::string& atom() const;
};

}