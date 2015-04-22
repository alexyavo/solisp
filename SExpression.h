#pragma once

#include <memory>
#include "LispObject.h"

namespace solisp {

class SExpression : public LispObject {
private:
  const std::shared_ptr<LispObject> m_first;
  const std::shared_ptr<LispObject> m_second;

public:
  SExpression(std::shared_ptr<LispObject> first, std::shared_ptr<LispObject> second);

  std::shared_ptr<LispObject> first() const;
  std::shared_ptr<LispObject> second() const;
};

class InvalidSExpression : public InvalidLispObject {
private:
  std::string m_sexp;

public:
  InvalidSExpression(const std::string& sexp) : m_sexp(sexp) {}
};

}