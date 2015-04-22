#include <iostream>
#include <assert.h>
#include <memory>

#include "utils/utils.h"
#include "Atom.h"
#include "Parser.h"
#include "SExpression.h"
#include "Interpreter.h"

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
}

void run_tests() {
  log_dbg("=== Running utils tests ===");
  RUN_TEST(trim);
  RUN_TEST(CharBuffer);
}

}
}

namespace solisp { namespace tests{

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

  assert(good0.eq(good1) == false);
  assert(Atom("BLA").eq(Atom("BLA")));
  assert(Atom("BLA").eq(Atom("BLA2")) == false);
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

void TEST_SExpressionParsing() {
  assert_invalid_sexp("k");
  assert_invalid_sexp("(FJFJfKK.F)");

  Parser parser;
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
}

void TEST_Interperter() {
  Interpreter().run();
}

void run_tests() {
  log_dbg("=== Running solisp tests === ");
  RUN_TEST(is_valid_atom);
  RUN_TEST(Atom);
  RUN_TEST(SExpressionParsing);
  RUN_TEST(Interperter);
}

}
}

int main() {
  utils::tests::run_tests();
  solisp::tests::run_tests();
  return 0;
}