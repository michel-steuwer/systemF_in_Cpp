#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <variant>
#include <utility>

namespace systemF {
  template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
  template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

  template<class... Ts> struct cases : Ts... { using Ts::operator()...; };
  template<class... Ts> cases(Ts...) -> cases<Ts...>;

  template <class Variant, class Visitor>
  auto match(Variant&& var, Visitor&& vis) {
      return std::visit(std::forward<Visitor>(vis), std::forward<Variant>(var));
  }

  template <class Variant1, class Variant2, class Visitor>
  auto match(Variant1&& var1, Variant2&& var2, Visitor&& vis) {
      return std::visit(std::forward<Visitor>(vis),
                        std::forward<Variant1>(var1), std::forward<Variant2>(var2));
  }

  auto freshName() -> std::string;

  template<class T, class U>
  bool compare_shared_ptr(const std::shared_ptr<T>& p1,
                          const std::shared_ptr<U>& p2) {
  if(p1 == p2) return true;
  if(p1 && p2) return *p1 == *p2;
  return false;
}

}

#endif // UTIL_H