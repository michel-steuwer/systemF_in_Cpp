#ifndef TYPE_H
#define TYPE_H

#include "util.h"

#include <variant>
#include <string>
#include <memory>

namespace systemF {
  struct Bool;
  struct Int;
  struct FunctionType;
  struct TypeVar;
  struct ForAll;
  using Type = std::variant<Bool, Int, FunctionType, TypeVar, ForAll>;

  struct Bool {};
  bool operator==(const Bool& lhs, const Bool& rhs);
  bool operator!=(const Bool& lhs, const Bool& rhs);

  struct Int {};
  bool operator==(const Int&, const Int&);
  bool operator!=(const Int&, const Int&);

  struct FunctionType {
    const std::shared_ptr<Type> inT;
    const std::shared_ptr<Type> outT;
    FunctionType(Type intT, Type outT);
  };
  bool operator==(const FunctionType& lhs, const FunctionType& rhs);
  bool operator!=(const FunctionType& lhs, const FunctionType& rhs);

  struct TypeVar {
    const std::string name;
    TypeVar(std::string name);
  };
  bool operator==(const TypeVar& lhs, const TypeVar& rhs);
  bool operator!=(const TypeVar& lhs, const TypeVar& rhs);

  struct ForAll {
    const std::shared_ptr<TypeVar> x;
    const std::shared_ptr<Type> t;
    ForAll(TypeVar x, Type t);
  };
  bool operator==(const ForAll& lhs, const ForAll& rhs);
  bool operator!=(const ForAll& lhs, const ForAll& rhs);
}

#endif // TYPE_H
