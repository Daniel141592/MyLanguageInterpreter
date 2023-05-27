#include "Typename.h"

Typename::Typename(Position p, ConstantType constantType) : Factor(p), type(constantType) {}

ConstantType Typename::getType() const {
    return type;
}

void Typename::accept(Visitor *visitor) const {
    visitor->visit(this);
}
