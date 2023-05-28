#include "NegatedExpression.h"

NegatedExpression::NegatedExpression(NegatedExpression::ExpressionPtr e)
                                                : Expression(e->getPosition()), expression(std::move(e)) {

}

const NegatedExpression::ExpressionPtr &NegatedExpression::getExpression() const {
    return expression;
}

void NegatedExpression::accept(Visitor& visitor) const {
    visitor.visit(*this);
}
