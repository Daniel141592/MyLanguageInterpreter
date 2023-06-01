#ifndef CODE_NEGATEDEXPRESSION_H
#define CODE_NEGATEDEXPRESSION_H

#include "Expression.h"
#include "NegationType.h"

class NegatedExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    NegationType negationType;
    ExpressionPtr expression;
public:
    NegatedExpression(ExpressionPtr e, NegationType type);
    const ExpressionPtr &getExpression() const;
    NegationType getNegationType() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_NEGATEDEXPRESSION_H
