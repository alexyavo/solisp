#include "Parser.h"
#include "SExpression.h"

#include <list>

namespace solisp {

Parser::Parser(bool strict) : m_strict(strict), m_environment(std::make_shared<Environment>()) {}
Parser::Parser(std::shared_ptr<const Environment> env, bool strict) : m_strict(strict), m_environment(env) {}

std::shared_ptr<LispObject> Parser::parse(utils::CharBuffer&& input) {
    return parse(input);
}

std::shared_ptr<LispObject> Parser::parse(utils::CharBuffer& input) {
  return m_strict ? parse_strict(input) : parse_relaxed(input);
}

std::shared_ptr<LispObject> Parser::parse_strict(utils::CharBuffer& input) {
  input.skip_whitespace();

  if (!input.has_remaining())
    return Nil;

  std::shared_ptr<LispObject> first, second;

  if (input.peek() != SEXP_OPEN) {
    return parse_atom(input);
  }
  else {
    input.skip(1); // skip SEXP_OPEN
    first = parse(input); // recursively parse first part of s-exp
  }

  input.skip_whitespace();
  must_read(input, SEXP_SEPERATOR);
  input.skip_whitespace();
  second = parse(input); // recursively parse second part of s-exp
  must_read(input, SEXP_CLOSE);

  return std::make_shared<SExpression>(first, second);
}



std::shared_ptr<LispObject> Parser::parse_relaxed(utils::CharBuffer& input) {
  input.skip_whitespace();
  if (!input.has_remaining())
    return Nil;
  if (input.peek() == SEXP_OPEN) {
    input.skip(1);
    auto result = parse_sexp(input);
    must_read(input, SEXP_CLOSE);
    return result;
  }

  return parse_atom(input);
}

std::shared_ptr<LispObject> Parser::parse_sexp(utils::CharBuffer& input) {
  std::list<std::shared_ptr<LispObject>> sexpObjects;
  std::shared_ptr<LispObject> result = Nil;

  input.skip_whitespace();
  while (input.has_remaining()) {
    switch (input.peek()) {
      case SEXP_OPEN:
        input.skip(1); // skip SEXP_OPEN
        sexpObjects.push_back(parse_sexp(input));
        input.skip_whitespace();
        must_read(input, SEXP_CLOSE);
        break;

      case SEXP_SEPERATOR:
        // If this s-exp is in dot notation it means i must have exactly two non empty parts
        if (sexpObjects.size() != 1)
          throw InvalidSExpression(input.get_str());

        input.skip(1); // skip SEXP_SEPERATOR
        input.skip_whitespace();
        if (!input.has_remaining())
          throw InvalidSExpression(input.get_str());

        if (isupper(input.peek())) {
          return std::make_shared<SExpression>(sexpObjects.front(), parse_atom(input));
        }
        else if (input.peek() == SEXP_OPEN) {
          input.skip(1);
          return std::make_shared<SExpression>(sexpObjects.front(), parse_sexp(input));
        }
        else {
          throw InvalidSExpression(input.get_str());
        }

      case SEXP_CLOSE:
        sexpObjects.reverse();
        for (auto sexp : sexpObjects) {
          result = std::make_shared<SExpression>(sexp, result);
        }
        return result;

      default:
        sexpObjects.push_back(parse_atom(input));
        break;
    }

    input.skip_whitespace();
  }

  // valid s-exp should encounter SEXP_CLOSE and return from that case
  throw InvalidSExpression(input.get_str());
}

std::shared_ptr<Atom> Parser::parse_atom(utils::CharBuffer& input) {
  return std::make_shared<Atom>(input.read_until([] (const utils::CharBuffer& buff) {
    char nextCh = buff.peek();
    return isalpha(nextCh) || isdigit(nextCh);
  }));
}

char Parser::must_read(utils::CharBuffer& input, char ch) {
  char inputCh;
  try {
    inputCh = input.read();
  }
  catch (const utils::BufferUnderflowException& ex) {
    throw InvalidSExpression(input.get_str());
  }

  if (inputCh != ch)
    throw InvalidSExpression(input.get_str());

  return ch;
}

}
