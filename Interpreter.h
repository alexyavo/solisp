#pragma once

#include <iostream>
#include "Environment.h"
#include "Parser.h"

namespace solisp {

class Interpreter {
private:
  std::shared_ptr<Environment> m_environment;
  Parser m_parser;

public:
  Interpreter();

  void run();

private:
  std::string read();
  std::shared_ptr<LispObject> eval(const std::string& input);
  void print(const LispObject& obj);
};

}