#include "MatchExpression.h"

MatchExpression::MatchExpression(MatchExpression::ExpressionPtr e, IdentifierPtr id, Block::BlockPtr b)
                                : expression(std::move(e)), identifier(std::move(id)), MatchStatement(std::move(b)) {

}

const MatchExpression::ExpressionPtr &MatchExpression::getExpression() const {
    return expression;
}

const Identifier::IdentifierPtr &MatchExpression::getIdentifier() const {
    return identifier;
}

void MatchExpression::accept(const Visitor *visitor) const {
    visitor->visit(this);
}


