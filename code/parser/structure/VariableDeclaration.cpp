#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(IdentifierPtr i, bool m) : identifier(std::move(i)), mut(m) {

}

VariableDeclaration::VariableDeclaration(IdentifierPtr i, std::unique_ptr<Expression> e, bool m)
                                : identifier(std::move(i)), mut(m), expression(std::move(e)) {

}

void VariableDeclaration::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

bool VariableDeclaration::isMut() const {
    return mut;
}

const VariableDeclaration::IdentifierPtr& VariableDeclaration::getIdentifier() const {
    return identifier;
}

const std::unique_ptr<Expression> &VariableDeclaration::getExpression() const {
    return expression;
}
