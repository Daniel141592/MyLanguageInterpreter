#include "OrExpression.h"

OrExpression::OrExpression(Position p, OrExpression::ExpressionPtr l, OrExpression::ExpressionPtr r)
                            : Expression(p), left(std::move(l)), right(std::move(r)) {
}

void OrExpression::accept(const Visitor *visitor) const {
    visitor->visit(this);
}

const OrExpression::ExpressionPtr &OrExpression::getLeft() const {
    return left;
}

const OrExpression::ExpressionPtr &OrExpression::getRight() const {
    return right;
}
