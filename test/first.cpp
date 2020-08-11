#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>

#include "systemF/expr.h"
#include "systemF/type.h"
#include "systemF/typecheck.h"
#include "systemF/show.h"

using namespace systemF;

TEST_CASE("identity") {
  auto l = TLambda(
    TypeVar("a"),
    Lambda(Var("x", TypeVar("a")), Var("x", TypeVar("a")))
  );
  std::cout << show(l) << "\n";
  std::cout << "Type: " << show(typeCheck(l)) << "\n";
}

template <typename F>
auto lambda(Type t, F body) -> Lambda {
    auto x = Var(freshName(), t);
    return Lambda(x, body(x));
}

template <typename F>
auto tLambda(F body) -> TLambda {
    auto x = TypeVar(freshName());
    return TLambda(x, body(x));
}

TEST_CASE("identity-dsl") {
  auto l = tLambda([](auto a){
    return lambda(a, [](auto x){
      return x;
    });
  });
  std::cout << show(l) << "\n";
  std::cout << "Type: " << show(typeCheck(l)) << "\n";
}
