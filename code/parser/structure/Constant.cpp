#include "Constant.h"

const std::variant<int, double, std::string> &Constant::getValue() const {
    return value;
}

ConstantType Constant::getConstantType() const {
    return constantType;
}

Constant::Constant(Position p, int v) : Factor(p), value(v) {
    constantType = ConstantType::INTEGER;
}

Constant::Constant(Position p, double v) : Factor(p), value(v) {
    constantType = ConstantType::FLOAT;
}

Constant::Constant(Position p, std::string v) : Factor(p), value(v) {
    constantType = ConstantType::STRING;
}

void Constant::accept(Visitor& visitor) const {
    visitor.visit(this);
}
