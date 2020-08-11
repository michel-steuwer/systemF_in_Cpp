#include "systemF/expr.h"
#include "systemF/typecheck.h"

#include <exception>

namespace systemF {


Var::Var(std::string name)
    :   name{std::move(name)}
    {};

Var::Var(std::string name, Type type)
    :   name{std::move(name)}, type{std::move(type)}
    {};

bool operator==(const Var& lhs, const Var& rhs) {
    return lhs.name == rhs.name;
}

bool operator!=(const Var& lhs, const Var& rhs) {
    return !(lhs == rhs);
}

bool operator<(const Var& lhs, const Var& rhs) {
    return lhs.name < rhs.name;
}

bool operator<=(const Var& lhs, const Var& rhs) {
    return lhs.name <= rhs.name;
}

bool operator>(const Var& lhs, const Var& rhs) {
    return lhs.name > rhs.name;
}

bool operator>=(const Var& lhs, const Var& rhs) {
    return lhs.name >= rhs.name;
}


Lambda::Lambda(Var x, Expr e)
    :   x{std::make_shared<Var>(x)},
        e{std::make_shared<Expr>(e)}
    {};

bool operator==(const Lambda& lhs, const Lambda& rhs) {
  return compare_shared_ptr(lhs.x, rhs.x)
      && compare_shared_ptr(lhs.e, rhs.e);
}

bool operator!=(const Lambda& lhs, const Lambda& rhs) {
    return !(lhs == rhs);
}

Apply::Apply(Expr f, Expr e)
    :   f{std::make_shared<Expr>(f)},
        e{std::make_shared<Expr>(e)}
    {};

bool operator==(const Apply& lhs, const Apply& rhs) {
  return compare_shared_ptr(lhs.f, rhs.f)
      && compare_shared_ptr(lhs.e, rhs.e);
}

bool operator!=(const Apply& lhs, const Apply& rhs) {
  return !(lhs == rhs);
}

TLambda::TLambda(TypeVar x, Expr e)
    :   x{x},
        e{std::make_shared<Expr>(e)}
    {};

bool operator==(const TLambda& lhs, const TLambda& rhs) {
  return (lhs.x == rhs.x)
      && compare_shared_ptr(lhs.e, rhs.e);
}

bool operator!=(const TLambda& lhs, const TLambda& rhs) {
    return !(lhs == rhs);
}


TApply::TApply(Expr f, Type t)
    :   f{std::make_shared<Expr>(f)},
        t{t}
    {};

bool operator==(const TApply& lhs, const TApply& rhs) {
  return compare_shared_ptr(lhs.f, rhs.f)
      && (lhs.t == rhs.t);
}

bool operator!=(const TApply& lhs, const TApply& rhs) {
  return !(lhs == rhs);
}

UnaryOp::UnaryOp(UnaryOp::Op op, Expr expr)
    :   op{op},
        expr{std::make_shared<Expr>(expr)}
    {};

bool operator==(const UnaryOp& lhs, const UnaryOp& rhs) {
  return lhs.op == rhs.op
      && compare_shared_ptr(lhs.expr, rhs.expr);
}

bool operator!=(const UnaryOp& lhs, const UnaryOp& rhs) {
  return !(lhs == rhs);
}


BinOp::BinOp(BinOp::Op op, Expr lhs, Expr rhs)
    :   op{op},
        lhs{std::make_shared<Expr>(lhs)},
        rhs{std::make_shared<Expr>(rhs)}
    {};

bool operator==(const BinOp& lhs, const BinOp& rhs) {
  return lhs.op == rhs.op
      && compare_shared_ptr(lhs.lhs, rhs.lhs)
      && compare_shared_ptr(lhs.rhs, rhs.rhs);
}

bool operator!=(const BinOp& lhs, const BinOp& rhs) {
  return !(lhs == rhs);
}


Literal::Literal(std::string literal, Type type)
    :   literal{literal},
        type{type}
    {};

bool operator==(const Literal& lhs, const Literal& rhs) {
  return lhs.literal == rhs.literal
      && lhs.type == rhs.type;
}

bool operator!=(const Literal& lhs, const Literal& rhs) {
  return !(lhs == rhs);
}

}