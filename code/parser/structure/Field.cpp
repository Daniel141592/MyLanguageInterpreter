#include "Field.h"

Field::Field(Position p, Field::ExpressionPtr e, FieldType type) : Factor(p), expression(std::move(e)), fieldType(type) {

}

const Field::ExpressionPtr &Field::getExpression() const {
    return expression;
}

FieldType Field::getFieldType() const {
    return fieldType;
}

void Field::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
