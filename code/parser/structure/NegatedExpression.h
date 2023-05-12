#ifndef CODE_NEGATEDEXPRESSION_H
#define CODE_NEGATEDEXPRESSION_H

#include "Expression.h"

class NegatedExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr expression;
public:
    NegatedExpression(ExpressionPtr e);
    const ExpressionPtr &getExpression() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_NEGATEDEXPRESSION_H
