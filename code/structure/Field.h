#ifndef CODE_FIELD_H
#define CODE_FIELD_H

#include "Factor.h"
#include "FieldType.h"

class Field : public Factor {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr expression;
    FieldType fieldType;
public:
    Field(Position p, ExpressionPtr e, FieldType type);
    const ExpressionPtr &getExpression() const;
    FieldType getFieldType() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_FIELD_H
