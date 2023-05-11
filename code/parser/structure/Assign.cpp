#include "Assign.h"

Assign::Assign(const Identifier &i, std::unique_ptr<Expression> e) : identifier(i), expression(std::move(e)) {

}

const Identifier &Assign::getIdentifier() const {
    return identifier;
}

const std::unique_ptr<Expression> &Assign::getExpression() const {
    return expression;
}

void Assign::accept(const Visitor* visitor) const {
    visitor->visit(this);
}


