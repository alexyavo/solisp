#include "Interpreter.h"
#include "elementary_functions.h"

namespace solisp {


Interpreter::Interpreter() :
    m_environment(std::make_shared<Environment>()),
    m_parser(m_environment)
{}


void Interpreter::run() {
    //    while (true) {
  print(*eval(read()));
    //    }
}

std::string Interpreter::read() {
  std::string input;
  getline(std::cin, input);
  return input;
}

std::shared_ptr<LispObject> Interpreter::eval(const std::string& input) {
  auto obj = m_parser.parse(utils::CharBuffer(input));
  if (! utils::instance_of<SExpression>(obj)) {
    return obj;
  }

  auto sexp = std::dynamic_pointer_cast<const SExpression>(obj);
  if (atom(*first(*sexp))) {
    auto firstAtom = std::dynamic_pointer_cast<Atom>(first(*sexp));
    if (*firstAtom == Atom("EQ")) {
      //return eq(*first(*rest(*sexp)), *first(*rest(*rest(*sexp))));
    }

  }
  else {

  };
}

void Interpreter::print(const LispObject& obj) {
  obj.print(std::cout);
}

}
