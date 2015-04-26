#pragma once

#include <memory>
#include "SExpression.h"
#include "Atom.h"

namespace solisp {

std::shared_ptr<SExpression> cons(std::shared_ptr<LispObject> first,
                                  std::shared_ptr<LispObject> second);

std::shared_ptr<LispObject> first(const SExpression& sexp);
std::shared_ptr<LispObject> rest(const SExpression& sexp);

std::shared_ptr<BooleanAtom> eq(const Atom& first, const Atom& second);
bool atom(const LispObject& obj);

}
