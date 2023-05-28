#include "Assign.h"

Assign::Assign(IdentifierPtr i, std::unique_ptr<Expression> e) : identifier(std::move(i)), expression(std::move(e)) {

}

const Assign::IdentifierPtr &Assign::getIdentifier() const {
    return identifier;
}

const std::unique_ptr<Expression> &Assign::getExpression() const {
    return expression;
}

void Assign::accept(Visitor& visitor) const {
    visitor.visit(*this);
}


