#ifndef TYPECHECKER_H
#define TYPECHECKER_H
#include <optional>
#include <vector>
#include <tuple>
#include <string>

#include "expr.h"

namespace systemF {

  namespace typeerror {
    struct expected {
      std::string str;
      expected(const std::string& str);
      expected(const Type& t);
    };

    struct found {
      std::string str;
      found(const std::string& str);
      found(const Type& t);
    };
  }

  struct TypeError : public std::logic_error {
    TypeError(const std::string& msg);

    TypeError(const typeerror::expected& expected, const typeerror::found& found);
    TypeError(const typeerror::found& found, const typeerror::expected& expected);
  };

  using TermContext = std::vector<std::tuple<std::string, Type>>;
  using TypeContext = std::vector<std::tuple<std::string, Type>>;

  auto typeCheck(const Expr& expr) -> Type;

  auto typeCheck(TermContext ctx, TypeContext tctx, const Expr& expr) -> Type;

} // namespace systemF

#endif // TYPECHECKER_H