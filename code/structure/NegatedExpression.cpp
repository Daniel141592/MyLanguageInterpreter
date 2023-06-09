#include "NegatedExpression.h"

NegatedExpression::NegatedExpression(NegatedExpression::ExpressionPtr e, NegationType type)
                      : Expression(e->getPosition()), expression(std::move(e)), negationType(type) {

}

const NegatedExpression::ExpressionPtr &NegatedExpression::getExpression() const {
    return expression;
}

void NegatedExpression::accept(Visitor &visitor) const {
    visitor.visit(*this);
}

NegationType NegatedExpression::getNegationType() const {
    return negationType;
}
