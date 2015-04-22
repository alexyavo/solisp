#include "Parser.h"
#include "SExpression.h"

namespace solisp {

Parser::Parser() : m_environment(std::make_shared<Environment>()) {}
Parser::Parser(std::shared_ptr<const Environment> env) : m_environment(env) {}

std::shared_ptr<LispObject> Parser::parse(utils::CharBuffer&& input) {
  return parse(input);
}

std::shared_ptr<LispObject> Parser::parse(utils::CharBuffer& input) {
#define ENSURE_VALID_SEXP(cond)                     \
    do {                                            \
      if (!(cond)) {                                \
        throw InvalidSExpression(input.get_str());  \
      }                                             \
    } while (false)

  input.skip_whitespace();

  if (!input.has_remaining())
    return m_environment->nil_atom();

  if (input.peek() != SEXP_OPEN)
    return parseAtom(input);

  input.skip(1); // skip SEXP_OPEN

  auto first = parse(input);
  input.skip_whitespace();
  ENSURE_VALID_SEXP(input.read() == SEXP_SEPERATOR);
  input.skip_whitespace();
  auto second = parse(input);
  ENSURE_VALID_SEXP(input.read() == SEXP_CLOSE);

  return std::make_shared<SExpression>(first, second);
}

std::shared_ptr<Atom> Parser::parseAtom(utils::CharBuffer& input) {
  std::string atom{""};

  while (input.has_remaining() &&
         input.peek() != SEXP_SEPERATOR &&
         input.peek() != SEXP_CLOSE)
  {
    atom.append(1, input.read());
  }

  return atom.empty() ?
         m_environment->nil_atom() :
         std::make_shared<Atom>(atom);
}

}
