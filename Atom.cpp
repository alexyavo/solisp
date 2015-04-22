#include "Atom.h"

namespace solisp {

Atom::Atom(const std::string& str) : m_str(str) {
  if (!is_valid_atom(m_str))
    throw InvalidAtom(m_str);
}

bool Atom::eq(const Atom& other) {
  return m_str == other.m_str;
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

}