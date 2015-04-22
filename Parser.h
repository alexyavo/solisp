#pragma once

#include "Environment.h"
#include "utils/utils.h"

namespace solisp {

class Parser {
private:
  std::shared_ptr<const Environment> m_environment;

public:
  Parser();
  Parser(std::shared_ptr<const Environment> env);

private:
  static const char SEXP_OPEN = '(';
  static const char SEXP_CLOSE = ')';
  static const char SEXP_SEPERATOR = '.';

public:
  std::shared_ptr<LispObject> parse(utils::CharBuffer& input);
  std::shared_ptr<LispObject> parse(utils::CharBuffer&& input);

private:
  std::shared_ptr<Atom> parseAtom(utils::CharBuffer& input);
};

}