#pragma once

#include "Environment.h"
#include "utils/utils.h"
#include "SExpression.h"

namespace solisp {

class Parser {
private:
  const bool m_strict;
  std::shared_ptr<const Environment> m_environment;

public:
  Parser(bool strict = false);
  Parser(std::shared_ptr<const Environment> env, bool strict = false);

private:
  static const char SEXP_OPEN = '(';
  static const char SEXP_CLOSE = ')';
  static const char SEXP_SEPERATOR = '.';

public:
  std::shared_ptr<LispObject> parse(utils::CharBuffer& input);
  std::shared_ptr<LispObject> parse(utils::CharBuffer&& input);

private:
  // sexpressions must be of form (sexp . sexp)
  std::shared_ptr<LispObject> parse_strict(utils::CharBuffer& input);

  // allow for list notation
  std::shared_ptr<LispObject> parse_relaxed(utils::CharBuffer& input);

  /*
   * Reads a sequence of alpha-numeric chars and attempts to create
   * an Atom object from them
   */
  std::shared_ptr<Atom> parse_atom(utils::CharBuffer& input);

  /*
   * input is after the opening '(' and when method returns it
   * is before the closing ')'
   */
  std::shared_ptr<LispObject> parse_sexp(utils::CharBuffer& input);

  char must_read(utils::CharBuffer& input, char ch);
};

}