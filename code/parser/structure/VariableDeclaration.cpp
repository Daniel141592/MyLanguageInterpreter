#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(const Identifier& i, bool m) : identifier(std::move(i)), mut(m) {

}

VariableDeclaration::VariableDeclaration(const Identifier& i, std::unique_ptr<Expression> e, bool m)
                                : identifier(i), mut(m), expression(std::move(e)) {

}

void VariableDeclaration::accept(const Visitor* visitor) const {
    visitor->visit(this);
}

bool VariableDeclaration::isMut() const {
    return mut;
}

const Identifier &VariableDeclaration::getIdentifier() const {
    return identifier;
}

const std::optional<std::unique_ptr<Expression>> &VariableDeclaration::getExpression() const {
    return expression;
}
