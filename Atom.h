#pragma once

#include <string>
#include <memory>

#include "LispObject.h"

namespace solisp {

class Atom : public LispObject {
private:
  const std::string m_str;

public:
  Atom(const std::string& str);
  virtual ~Atom();

  bool operator==(const Atom& other) const;
  bool operator!=(const Atom& other) const;

  // LispObject interface
public:
  virtual void print(std::ostream& out) const override;

public:
  static bool is_valid_atom(const std::string& str);
  static bool is_valid_atom_char(char ch);
};

class BooleanAtom : public Atom {
public:
  BooleanAtom(bool isTrue);
};

class TrueAtom : public BooleanAtom {
public:
  TrueAtom();
};

class FalseAtom : public BooleanAtom {
public:
  FalseAtom();
};

class NilAtom : public Atom {
public:
  NilAtom();
};

extern const std::shared_ptr<TrueAtom> T;
extern const std::shared_ptr<FalseAtom> F;
extern const std::shared_ptr<NilAtom> Nil;

class InvalidAtom : public InvalidLispObject {
private:
  const std::string m_atom;

public:
  InvalidAtom(const std::string& atom);

  const std::string& atom() const;
};

}