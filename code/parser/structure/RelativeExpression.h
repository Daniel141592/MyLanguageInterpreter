#ifndef CODE_RELATIVEEXPRESSION_H
#define CODE_RELATIVEEXPRESSION_H

#include "Expression.h"
#include "RelativeType.h"

class RelativeExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr left;
    ExpressionPtr right;
    RelativeType relativeType;
public:
    RelativeExpression(Position p, ExpressionPtr l, ExpressionPtr r, RelativeType type);
    const ExpressionPtr &getLeft() const;
    const ExpressionPtr &getRight() const;
    RelativeType getRelativeType() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_RELATIVEEXPRESSION_H
