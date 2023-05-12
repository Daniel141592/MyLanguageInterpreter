#include "RelativeExpression.h"

RelativeExpression::RelativeExpression(Position p, RelativeExpression::ExpressionPtr l,
                                       RelativeExpression::ExpressionPtr r, RelativeType type)
                                        : Expression(p), left(std::move(l)), right(std::move(r)), relativeType(type) {

}

const RelativeExpression::ExpressionPtr &RelativeExpression::getLeft() const {
    return left;
}

const RelativeExpression::ExpressionPtr &RelativeExpression::getRight() const {
    return right;
}

RelativeType RelativeExpression::getRelativeType() const {
    return relativeType;
}

void RelativeExpression::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
