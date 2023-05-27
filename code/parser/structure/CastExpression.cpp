#include "CastExpression.h"

CastExpression::CastExpression(Position p, CastExpression::ExpressionPtr e, ConstantType t)
                                                : Expression(p), expression(std::move(e)), type(t) {

}

const CastExpression::ExpressionPtr &CastExpression::getExpression() const {
    return expression;
}

ConstantType CastExpression::getType() const {
    return type;
}

void CastExpression::accept(Visitor* visitor) const {
    visitor->visit(this);
}
