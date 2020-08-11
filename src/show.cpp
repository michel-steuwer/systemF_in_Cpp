#include "systemF/show.h"

#include <sstream>

namespace systemF {

auto show(const Expr& expr) -> std::string {
  std::stringstream buf;
  match(expr, cases {
    [&](const Var& v) {
      buf << v.name;
      if (v.type) {
        buf << ":" << show(v.type.value());
      }
    },
    [&](const Lambda& l) {
      buf << "\\" << show(*l.x) << ". " << show(*l.e) ;
    },
    [&](const Apply& a) {
      buf << "(" << show(*a.f) << ") " << show(*a.e);
    },
    [&](const TLambda& l) {
      buf << "/\\" << show(l.x) <<  ". " << show(*l.e);
    },
    [&](const TApply& a) {
      buf << "(" << show(*a.f) << ") " << show(a.t);
    },
    [&](const UnaryOp& u) {
      buf << show(u.op) << show(*u.expr);
    },
    [&](const BinOp& b) {
      buf << show(*b.lhs) << " " << show(b.op) << " " << show(*b.rhs);
    },
    [&](const Literal& l) {
      buf << l.literal;
    }
  });
  return buf.str();
}

auto show(const Type& type) -> std::string {
  std::stringstream buf;
  match(type, cases {
    [&](const Bool&)            { buf << "bool"; },
    [&](const Int&)             { buf << "int"; },
    [&](const FunctionType& f)  { buf << show(*f.inT) << "->" << show(*f.outT); },
    [&](const TypeVar& v)       { buf << v.name; },
    [&](const ForAll& f)        { buf << "\\/" << show(*f.x) << ". " << show(*f.t); }
  });
  return buf.str();
}

auto show(const UnaryOp::Op& op) -> std::string {
  switch (op) {
    case UnaryOp::Op::NEG: return "-";
  }
}

auto show(const BinOp::Op& op) -> std::string {
  switch (op) {
    case BinOp::Op::ADD:  return "+";
    case BinOp::Op::SUB:  return "-";
    case BinOp::Op::MULT: return "*";
  }
}

} // namespace systemF
