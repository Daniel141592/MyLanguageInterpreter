#ifndef CODE_ANDEXPRESSION_H
#define CODE_ANDEXPRESSION_H


#include <memory>
#include "Expression.h"

class AndExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr left;
    ExpressionPtr right;
public:
    AndExpression(Position p, ExpressionPtr l, ExpressionPtr r);
    ~AndExpression() override = default;
    void accept(Visitor* visitor) const override;

    const ExpressionPtr& getLeft() const;
    const ExpressionPtr& getRight() const;
};


#endif //CODE_ANDEXPRESSION_H
