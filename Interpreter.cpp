#include "Interpreter.h"

namespace solisp {


Interpreter::Interpreter() :
    m_environment(std::make_shared<Environment>()),
    m_parser(m_environment)
{}


void Interpreter::run() {
    //    while (true) {
    //    eval(read());
    //    }

}

std::string Interpreter::read() {
  std::string input;
  getline(std::cin, input);
  return input;
}

void Interpreter::eval(const std::string& input) {

}

}
