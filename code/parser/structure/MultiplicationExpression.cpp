#include "MultiplicationExpression.h"

MultiplicationExpression::MultiplicationExpression(Position p, MultiplicationExpression::ExpressionPtr l,
                                                   MultiplicationExpression::ExpressionPtr r, MultiplicativeType type)
                                   : Expression(p), left(std::move(l)), right(std::move(r)), multiplicativeType (type) {

}

const MultiplicationExpression::ExpressionPtr &MultiplicationExpression::getLeft() const {
    return left;
}

const MultiplicationExpression::ExpressionPtr &MultiplicationExpression::getRight() const {
    return right;
}

MultiplicativeType MultiplicationExpression::getMultiplicativeType() const {
    return multiplicativeType;
}

void MultiplicationExpression::accept(Visitor* visitor) const {
    visitor->visit(this);
}

