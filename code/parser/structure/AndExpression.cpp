#include "AndExpression.h"

AndExpression::AndExpression(Position p, AndExpression::ExpressionPtr l, AndExpression::ExpressionPtr r)
        : Expression(p), left(std::move(l)), right(std::move(r)) {
}

void AndExpression::accept(Visitor* visitor) const {
    visitor->visit(this);
}

const AndExpression::ExpressionPtr &AndExpression::getLeft() const {
    return left;
}

const AndExpression::ExpressionPtr &AndExpression::getRight() const {
    return right;
}
