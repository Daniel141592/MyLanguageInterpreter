#ifndef CODE_CASTEXPRESSION_H
#define CODE_CASTEXPRESSION_H

#include "Expression.h"
#include "ConstantType.h"

class CastExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr expression;
    ConstantType type;
public:
    CastExpression(Position p, ExpressionPtr e, ConstantType t);
    const ExpressionPtr &getExpression() const;
    ConstantType getType() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_CASTEXPRESSION_H
