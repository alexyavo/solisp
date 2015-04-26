#include "Atom.h"

namespace solisp {

Atom::Atom(const std::string& str) : m_str(str) {
  if (!is_valid_atom(m_str))
    throw InvalidAtom(m_str);
}

bool Atom::is_valid_atom(const std::string& str) {
  if (str.length() == 0)
    return false;
  if (!isupper(str[0]))
    return false;

  for (const char& ch : str) {
    if (!isdigit(ch) && !isupper(ch))
      return false;
  }

  return true;
}

InvalidAtom::InvalidAtom(const std::string& atom) : m_atom(atom) {}

const std::string& InvalidAtom::atom() const {
  return m_atom;
}

bool Atom::is_valid_atom_char(char ch) {
  return isupper(ch) || isdigit(ch);
}

bool Atom::operator==(const Atom& other) const {
  return m_str == other.m_str;
}

bool Atom::operator!=(const Atom& other) const {
  return !(*this == other);
}

void Atom::print(std::ostream& out) const {
  out << m_str.c_str();
}

Atom::~Atom() {
}

BooleanAtom::BooleanAtom(bool isTrue) : Atom(isTrue ? "T" : "F") {}
TrueAtom::TrueAtom() : BooleanAtom(true) {}
FalseAtom::FalseAtom() : BooleanAtom(false) {}
NilAtom::NilAtom() : Atom("NIL") {}

const std::shared_ptr<TrueAtom> T = std::make_shared<TrueAtom>();
const std::shared_ptr<FalseAtom> F = std::make_shared<FalseAtom>();
const std::shared_ptr<NilAtom> Nil = std::make_shared<NilAtom>();

}