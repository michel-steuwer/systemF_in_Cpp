#include "systemF/type.h"
#include "systemF/util.h"

namespace systemF {

  FunctionType::FunctionType(Type intT, Type outT)
      :   inT{std::make_shared<Type>(intT)},
          outT{std::make_shared<Type>(outT)}
      {};

  TypeVar::TypeVar(std::string name)
      : name{name}
      {};

  ForAll::ForAll(TypeVar x, Type t)
  :   x{std::make_shared<TypeVar>(x)},
      t{std::make_shared<Type>(t)}
  {};

  bool operator==(const Bool&, const Bool&) {
    return true;
  }

  bool operator!=(const Bool& lhs, const Bool& rhs) {
    return !(lhs == rhs);
  }

  bool operator==(const Int&, const Int&) {
    return true;
  }

  bool operator!=(const Int& lhs, const Int& rhs) {
    return !(lhs == rhs);
  }

  bool operator==(const FunctionType& lhs, const FunctionType& rhs) {
    return compare_shared_ptr(lhs.inT, rhs.inT)
      && compare_shared_ptr(lhs.outT, rhs.outT);
  }

  bool operator!=(const FunctionType& lhs, const FunctionType& rhs) {
    return !(lhs == rhs);
  }

  bool operator==(const TypeVar& lhs, const TypeVar& rhs) {
    return lhs.name == rhs.name;
  }

  bool operator!=(const TypeVar& lhs, const TypeVar& rhs) {
    return !(lhs == rhs);
  }

  bool operator==(const ForAll& lhs, const ForAll& rhs) {
    return compare_shared_ptr(lhs.x, rhs.x)
        && compare_shared_ptr(lhs.t, rhs.t);
  }

  bool operator!=(const ForAll& lhs, const ForAll& rhs) {
    return !(lhs == rhs);
  }

}