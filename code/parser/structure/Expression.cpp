#include "Expression.h"

Expression::Expression(Expression::ExpressionPtr l, Expression::ExpressionPtr r)
                            : left(std::move(l)), right(std::move(r)) {

}

void Expression::accept(const Visitor *visitor) const {
    visitor->visit(this);
}

const Expression::ExpressionPtr &Expression::getLeft() const {
    return left;
}

const Expression::ExpressionPtr &Expression::getRight() const {
    return right;
}
