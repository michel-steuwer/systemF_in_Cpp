#ifndef SHOW_H
#define SHOW_H

#include <string>

#include "expr.h"

namespace systemF {

  auto show(const Expr& expr) -> std::string;

  auto show(const Type& type) -> std::string;

  auto show(const UnaryOp::Op& op) -> std::string;

  auto show(const BinOp::Op& op) -> std::string;

} // namespace systemF

#endif // SHOW_H
