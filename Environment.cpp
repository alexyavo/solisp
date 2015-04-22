#include "Environment.h"

namespace solisp {

Environment::Environment() :
    m_true(std::make_shared<Atom>("T")),
    m_false(std::make_shared<Atom>("F")),
    m_nil(std::make_shared<Atom>("NIL"))
{}

std::shared_ptr<Atom> Environment::true_atom() const {
  return m_true;
}

std::shared_ptr<Atom> Environment::false_atom() const {
  return m_false;
}

std::shared_ptr<Atom> Environment::nil_atom() const {
  return m_nil;
}

}