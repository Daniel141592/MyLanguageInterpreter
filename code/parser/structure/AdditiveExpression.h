#ifndef CODE_ADDITIVEEXPRESSION_H
#define CODE_ADDITIVEEXPRESSION_H

#include "Expression.h"
#include "AdditiveType.h"

class AdditiveExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr left;
    ExpressionPtr right;
    AdditiveType additiveType;
public:
    AdditiveExpression(Position p, ExpressionPtr l, ExpressionPtr r, AdditiveType type);
    const ExpressionPtr &getLeft() const;
    const ExpressionPtr &getRight() const;
    AdditiveType getAdditiveType() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_ADDITIVEEXPRESSION_H
