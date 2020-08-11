#include <variant>
#include <optional>
#include <iostream>
#include <vector>
#include <string>

#include "systemF/typecheck.h"
#include "systemF/expr.h"
#include "systemF/type.h"
#include "systemF/show.h"
#include "systemF/util.h"

namespace systemF {

auto success = std::optional<TypeError>{};

auto error(std::string found, std::string expected) -> std::optional<TypeError> {
    return std::make_optional<TypeError>(
        "Type error: found " + found + " expected " + expected);
}

auto error(const Type& found, const Type& expected) -> std::optional<TypeError> {
    return error(show(found), show(expected));
}

auto check(const Type& found, const Type& expected) -> std::optional<TypeError> {
    if (found != expected) {
        return error(found, expected);
    } else {
        return success;
    }
}

TypeError::TypeError(const std::string& msg)
    :   logic_error{msg}
    {};

TypeError::TypeError(const typeerror::expected& expected, const typeerror::found& found)
    :   logic_error{"Expected " + expected.str + " but found " + found.str}
    {};

TypeError::TypeError(const typeerror::found& found, const typeerror::expected& expected)
    :   logic_error{"Expected " + expected.str + " but found " + found.str}
    {};

namespace typeerror {

expected::expected(const std::string& str)
    : str{str}
    {};

expected::expected(const Type& t)
    : str{show(t)}
    {};

found::found(const std::string& str)
    : str{str}
    {};

found::found(const Type& t)
    : str{show(t)}
    {};

}

auto freetvars(const Type& type) -> std::vector<std::string> {
  return match(type, cases {
    [&](const Var& v) -> std::vector<std::string> {
      return {v.name};
    },
    [&](const ForAll& f) -> std::vector<std::string> {
      auto ftvars = freetvars(*f.t);
      ftvars.erase(std::remove(ftvars.begin(), ftvars.end(), f.x->name), ftvars.end());
      return ftvars;
    },
    [&](const FunctionType& ft) -> std::vector<std::string> {
      auto ftvarsIn = freetvars(*ft.inT);
      auto ftvarsOut = freetvars(*ft.outT);
      ftvarsIn.insert(ftvarsIn.end(), ftvarsOut.begin(), ftvarsOut.end());
      return ftvarsIn;
    },
    [&](const auto&) -> std::vector<std::string> {
      return {};
    }
  });
}

auto isInFreetvars(const std::string& name, const std::vector<std::string>& ftvars) -> bool {
  return (std::find(ftvars.begin(), ftvars.end(), name) != ftvars.end());
}

auto typesubs(const Type& ty,
              const TypeVar& forTy,
              const Type& in) -> Type {
  auto x = forTy;
  return match(in, cases {
    [&](const ForAll& f) -> Type {
      if (auto v = f.x.get(); v && *v != x && !isInFreetvars(v->name, freetvars(ty))) {
        return ForAll(*v, typesubs(ty, x, *f.t));
      }
      return in;
    }, 
    [&](const FunctionType& f) -> Type {
      return FunctionType(typesubs(ty, x, *f.inT), typesubs(ty, x, *f.outT));
    },
    [&](const TypeVar& v) -> Type {
      if (x == v) {
        return ty;
      } else {
        return v;
      }
    },
    [&](const auto& t) -> Type {
      return t;
    }
  });
}

auto lookupVarInEnv(const Var& v, const TermContext& ctx) -> Type {
  auto t = std::find_if(ctx.begin(), ctx.end(), [&](const auto& x){
    return std::get<0>(x) == v.name;
  });
  if (t != ctx.end()) {
    return std::get<1>(*t);
  } else {
    throw TypeError("Unreferenced Variable used");
  }
}

auto lookupTypeInEnv(const Type& type, const TypeContext& tctx) -> Type {
  return match(type, cases {
    [&](const TypeVar& v) {
      auto t = std::find_if(tctx.begin(), tctx.end(), [&](const auto& x) {
        return std::get<0>(x) == v.name;
      });
      if (t != tctx.end()) {
        return std::get<1>(*t);
      } else {
        throw TypeError("Unreferenced Type Variable used");
      }
    },
    [&](const auto&) { return type; }
  });
}

auto typeCheck(const Expr& expr) -> Type {
  auto ctx = TermContext{};
  auto tctx = TypeContext{};
  return typeCheck(ctx, tctx, expr);
}

auto typeCheck(TermContext ctx, TypeContext tctx, const Expr& expr) -> Type {
  return match(expr, cases {
    [&](const Var& v) -> Type {
      return lookupVarInEnv(v, ctx);
    },
    [&](const Lambda& l) -> Type {
      if (!l.x->type.has_value()) { throw TypeError("Lambda without parameter type"); } ;
      auto type = lookupTypeInEnv(l.x->type.value(), tctx);
      ctx.push_back({l.x->name, type});
      return FunctionType(type, typeCheck(ctx, tctx, *l.e));
    },
    [&](const Apply& a) -> Type {
      auto t1 = typeCheck(ctx, tctx, *a.f);
      auto t2 = typeCheck(ctx, tctx, *a.e);
      return match(t1, cases {
        [&](const FunctionType& ft) -> Type {
          if (*ft.inT == t2) {
            return *ft.outT;
          } else {
            throw TypeError("Argument of application doesn't match abstraction");
          }
        },
        [&](const auto&) -> Type {
          throw TypeError("Not a function");
        }
      });
    },
    [&](const TLambda& l) -> Type {
      tctx.push_back({l.x.name, l.x});
      return ForAll(l.x, typeCheck(ctx, tctx, *l.e));
    },
    [&](const TApply& a) -> Type {
      auto t1 = typeCheck(ctx, tctx, *a.f);
      return match(t1, cases {
        [&](const ForAll& f) -> Type {
          return typesubs(a.t, *f.x, *f.t);
        },
        [](const auto&) -> Type {
          throw TypeError("Type application of non-type abstraction");
        }
      });
    },
    [&](const UnaryOp& u) -> Type {
      return typeCheck(ctx, tctx, *u.expr);
    },
    [&](const BinOp& b) -> Type {
      auto lhs = typeCheck(ctx, tctx, *b.lhs);
      auto rhs = typeCheck(ctx, tctx, *b.rhs);
      if (lhs == rhs) {
        return lhs;
      } else {
        throw TypeError("Types of operands of binary operations don;'t match");
      }
    },
    [&](const Literal& l) -> Type {
      return l.type;
    }
  });
}

} // namespace systemF