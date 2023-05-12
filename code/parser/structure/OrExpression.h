#ifndef CODE_OREXPRESSION_H
#define CODE_OREXPRESSION_H


#include <memory>
#include "Expression.h"

class OrExpression : public Expression {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr left;
    ExpressionPtr right;
public:
    OrExpression(Position p, ExpressionPtr l, ExpressionPtr r);
    ~OrExpression() override = default;
    void accept(const Visitor* visitor) const override;

    const ExpressionPtr& getLeft() const;
    const ExpressionPtr& getRight() const;
};


#endif //CODE_OREXPRESSION_H
