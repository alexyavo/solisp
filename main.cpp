#include <iostream>
#include <assert.h>
#include <memory>

#include "utils/utils.h"
#include "Atom.h"
#include "Parser.h"
#include "Interpreter.h"
#include "elementary_functions.h"

#define log_dbg(str) std::cout << str << std::endl

#define RUN_TEST(name)                          \
  std::cout << "[TEST] "#name << "... ";        \
  do {                                          \
    TEST_##name();                              \
        std::cout << "OK" << std::endl;         \
  } while(false)

namespace utils {
namespace tests {

using namespace ::utils;

using std::string;

void TEST_trim() {
  string s0{"blabla"};
  string s1{" blabla "};
  string s2{" bla bla "};
  string s3{"\t\t bla bla \t "};

  assert(trim(s0) == "blabla");
  assert(trim(s1) == "blabla");
  assert(trim(s2) == "bla bla");
  assert(trim(s3) == "bla bla");
}

void TEST_CharBuffer() {
  string test = "bla is the color";
  CharBuffer buff(test);

  assert(buff.remaining() == test.length());

  while (buff.has_remaining()) {
    char ch = buff.read();
    assert(ch == test[buff.position() - 1]);
  }

  try {
    buff.read();
    assert(false);
  }
  catch (const BufferUnderflowException& ex) {
    // ok
  }

  buff.set_position(0);
  assert(buff.remaining() == test.length());
  assert(buff.skip(100000) == test.length());

  try {
    buff.set_position(201010);
    assert(false);
  }
  catch (const BufferUnderflowException& ex) {
    // ok
  }

  buff.reset();
  assert(buff.remaining() == test.length());
  buff.set_position(buff.remaining() - 2);

  {
    CharBuffer buff("alex");
    buff.read_until([] (const CharBuffer& buff) {
      return buff.peek() != 'e';
    });
  }
}

void run_tests() {
  log_dbg("=== Running utils tests ===");
  RUN_TEST(trim);
  RUN_TEST(CharBuffer);
}

}
}

namespace solisp {
namespace tests {

using namespace ::solisp;
using std::string;
using std::dynamic_pointer_cast;

void TEST_is_valid_atom() {
  assert(Atom::is_valid_atom("blabla") == false);
  assert(Atom::is_valid_atom("1blabla") == false);
  assert(Atom::is_valid_atom("1blAAla") == false);
  assert(Atom::is_valid_atom("bBBf2la") == false);
  assert(Atom::is_valid_atom("bBBf2la") == false);
  assert(Atom::is_valid_atom("BB<") == false);
  assert(Atom::is_valid_atom("BB<BB2") == false);
  assert(Atom::is_valid_atom("BAD ATOM") == false);

  assert(Atom::is_valid_atom("GOOD"));
  assert(Atom::is_valid_atom("GOOD22"));
  assert(Atom::is_valid_atom("VERYGOOD"));
}

void assert_invalid_atom(const string& atom) {
  try {
    Atom a(atom);
    assert(false);
  }
  catch (const InvalidAtom& ex) {
    assert(ex.atom() == atom);
  }
}

void TEST_Atom() {
  assert_invalid_atom("blabla");
  assert_invalid_atom("SOMETHING NOT GOOD");

  Atom good0("BLABLA");
  Atom good1("BLA22AB");

  assert(good0 != good1);
  assert(Atom("BLA") == Atom("BLA"));
  assert(Atom("BLA") != Atom("BLA2"));
}

void assert_invalid_sexp(const string& sexp) {
  try {
    Parser().parse(utils::CharBuffer(sexp));
    assert(false);
  }
  catch (const InvalidLispObject& ex) {
    //ok
  }
}

void TEST_SExpressionStrictParsing() {
  assert_invalid_sexp("k");
  assert_invalid_sexp("(FJFJfKK.F)");

  Parser parser(true);
  {
    auto lobj = parser.parse(utils::CharBuffer("(A.A)"));
    assert(utils::instance_of<SExpression>(lobj.get()));

    auto sexp = dynamic_pointer_cast<const SExpression>(lobj);
    assert(utils::instance_of<Atom>(sexp->first()));
    assert(utils::instance_of<Atom>(sexp->second()));
  }

  {
    auto lobj = parser.parse(utils::CharBuffer("ATOM"));
    assert(utils::instance_of<Atom>(lobj));
  }

  {
    auto lobj = parser.parse(utils::CharBuffer("T"));
    assert(utils::instance_of<Atom>(lobj));
  }

  assert_invalid_sexp("((A1 . A2) . B");

  parser.parse(utils::CharBuffer("(A . (B .C))"));
  parser.parse(utils::CharBuffer("((A1 . A2) . B)"));
  parser.parse(utils::CharBuffer("((U .V) . (X. Y))"));
}

void TEST_SExpressionListNotationParsing() {
  Parser parser;
  parser.parse(utils::CharBuffer("(A B C)"));
  parser.parse(utils::CharBuffer("((A B) C)"));
  parser.parse(utils::CharBuffer("(A B (C D))"));
  parser.parse(utils::CharBuffer("(A)"));
  parser.parse(utils::CharBuffer("((A))"));
  parser.parse(utils::CharBuffer("(A (B .C ))"));
}

void TEST_elementary_functions() {
  Parser p;
  auto atom0 = std::make_shared<Atom>("A0");
  auto atom1 = std::make_shared<Atom>("A1");
  auto atom2 = std::make_shared<Atom>("A2");
  auto atom3 = std::make_shared<Atom>("A3");

  first(*cons(atom3, cons(atom0, atom1)));
  rest(*cons(atom2, atom1));
  assert(eq(*atom0, *atom0));
  assert(eq(*atom0, Atom("A0")));
  assert(eq(*atom0, *atom1) == false);
  assert(eq(*atom0, Atom("A0IIII")) == false);

  assert(atom(*atom0));
  assert(atom(*cons(atom0, atom1)) == false);
}

void TEST_Interperter() {
  Interpreter().run();
}

void run_tests() {
  log_dbg("=== Running solisp tests === ");
  RUN_TEST(is_valid_atom);
  RUN_TEST(Atom);
  RUN_TEST(SExpressionStrictParsing);
  RUN_TEST(SExpressionListNotationParsing);
  RUN_TEST(Interperter);
  RUN_TEST(elementary_functions);
}

}}

/*
 * symbol
 * define, defconst
 * apply searches symbols plist before going over the alist supplide as argument.
 * this alist contains the variable bindings - (e.g. "X" is actually "A" in this invocation)
 *
 * most functions are basically constants
 *
 * eval, apply, evalquote
 * evcon (is the implementatoin of COND that evaluates the arguments in correct order)
 *
 * what properties do atomic symbols have?
 * - PNAME: print name of the atomic symbol
 * - EXPR: sexp that defines the functions that is bound to the atomic symbol
 * - SUBR: assembly definition of function
 * - APVAL: permanent value for the atomic symbol considered as variable
 *
 *
 *
 * special forms:
 * COND,
 */

int main() {
  utils::tests::run_tests();
  solisp::tests::run_tests();
  return 0;
}