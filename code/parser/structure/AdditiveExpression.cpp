#include "AdditiveExpression.h"

AdditiveExpression::AdditiveExpression(Position p, AdditiveExpression::ExpressionPtr l,
                                       AdditiveExpression::ExpressionPtr r, AdditiveType type)
                                       : Expression(p), left(std::move(l)), right(std::move(r)), additiveType(type) {

}


const AdditiveExpression::ExpressionPtr &AdditiveExpression::getLeft() const {
    return left;
}

const AdditiveExpression::ExpressionPtr &AdditiveExpression::getRight() const {
    return right;
}

AdditiveType AdditiveExpression::getAdditiveType() const {
    return additiveType;
}

void AdditiveExpression::accept(Visitor& visitor) const {
    visitor.visit(this);
}
