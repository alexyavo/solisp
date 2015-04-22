#include "SExpression.h"

namespace solisp {

SExpression::SExpression(std::shared_ptr<LispObject> first, std::shared_ptr<LispObject> second) :
    m_first(first),
    m_second(second)
{}

std::shared_ptr<LispObject> SExpression::first() const {
  return m_first;
}

std::shared_ptr<LispObject> SExpression::second() const {
  return m_second;
}

}