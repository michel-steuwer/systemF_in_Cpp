#ifndef EXPR_H
#define EXPR_H

#include <variant>
#include <string>
#include <optional>
#include <map>

#include "type.h"
#include "util.h"

namespace systemF {

// simply typed lambda calculus
struct Var;
struct Lambda;
struct Apply;

// System F
struct TLambda;
struct TApply;

// scala language
struct UnaryOp;
struct BinOp;
struct Literal;

using Expr = std::variant<
    Var,
    Lambda,
    Apply,
    TLambda,
    TApply,
    UnaryOp,
    BinOp,
    Literal
    >;

struct Var {
    const std::string name;
    std::optional<Type> type;

    Var(std::string name);
    Var(std::string name, Type type);
};

bool operator==(const Var& lhs, const Var& rhs);
bool operator!=(const Var& lhs, const Var& rhs);
bool operator<(const Var& lhs, const Var& rhs);
bool operator<=(const Var& lhs, const Var& rhs);
bool operator>(const Var& lhs, const Var& rhs);
bool operator>=(const Var& lhs, const Var& rhs);

struct Lambda {
    const std::shared_ptr<Var> x;
    const std::shared_ptr<Expr> e;

    Lambda(Var x, Expr e);
};

bool operator==(const Lambda& lhs, const Lambda& rhs);
bool operator!=(const Lambda& lhs, const Lambda& rhs);

struct Apply {
    const std::shared_ptr<Expr> f;
    const std::shared_ptr<Expr> e;

    Apply(Expr f, Expr e);
};

bool operator==(const Apply& lhs, const Apply& rhs);
bool operator!=(const Apply& lhs, const Apply& rhs);

struct TLambda {
    TypeVar x;
    const std::shared_ptr<Expr> e;

    TLambda(TypeVar x, Expr e);
};

bool operator==(const TLambda& lhs, const TLambda& rhs);
bool operator!=(const TLambda& lhs, const TLambda& rhs);

struct TApply {
    const std::shared_ptr<Expr> f;
    Type t;

    TApply(Expr f, Type t);
};

bool operator==(const TApply& lhs, const TApply& rhs);
bool operator!=(const TApply& lhs, const TApply& rhs);


struct UnaryOp {
    enum class Op {
        NEG
    };
    const Op op;
    const std::shared_ptr<Expr> expr;

    UnaryOp(UnaryOp::Op op, Expr expr);
};

bool operator==(const UnaryOp& lhs, const UnaryOp& rhs);
bool operator!=(const UnaryOp& lhs, const UnaryOp& rhs);


struct BinOp {
    enum class Op {
        ADD,
        SUB,
        MULT
    };
    const Op op;
    const std::shared_ptr<Expr> lhs;
    const std::shared_ptr<Expr> rhs;

    BinOp(BinOp::Op op, Expr lhs, Expr rhs);
};

bool operator==(const BinOp& lhs, const BinOp& rhs);
bool operator!=(const BinOp& lhs, const BinOp& rhs);


struct Literal {
    const std::string literal;
    const Type type;

    Literal(std::string literal, Type type);
};

bool operator==(const Literal& lhs, const Literal& rhs);
bool operator!=(const Literal& lhs, const Literal& rhs);

} // namespace systemF

#endif // EXPR_H