#ifndef CODE_MULTIPLICATIONEXPRESSION_H
#define CODE_MULTIPLICATIONEXPRESSION_H

#include "Expression.h"
#include "MultiplicativeType.h"

class MultiplicationExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr left;
    ExpressionPtr right;
    MultiplicativeType multiplicativeType;
public:
    MultiplicationExpression(Position p, ExpressionPtr l, ExpressionPtr r, MultiplicativeType type);
    const ExpressionPtr &getLeft() const;
    const ExpressionPtr &getRight() const;
    MultiplicativeType getMultiplicativeType() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_MULTIPLICATIONEXPRESSION_H
