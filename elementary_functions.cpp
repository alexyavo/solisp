#include "elementary_functions.h"
#include "utils/utils.h"

namespace solisp {


std::shared_ptr<SExpression> cons(std::shared_ptr<LispObject> first, std::shared_ptr<LispObject> second) {
  return std::make_shared<SExpression>(first, second);
}


std::shared_ptr<LispObject> first(const SExpression& sexp) {
  return sexp.first();
}

std::shared_ptr<LispObject> rest(const SExpression& sexp) {
  return sexp.second();
}

std::shared_ptr<BooleanAtom> eq(const Atom& first, const Atom& second) {
  if (first == second)
    return T;
  else
    return F;
}

bool atom(const LispObject& obj) {
  return utils::instance_of<const Atom>(&obj);
}

}
