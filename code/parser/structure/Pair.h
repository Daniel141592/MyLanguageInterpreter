#ifndef CODE_PAIR_H
#define CODE_PAIR_H


#include "Expression.h"

class Pair : public Expression {
    using ExpressionPtr = Expression::ExpressionPtr;
    ExpressionPtr first;
    ExpressionPtr second;
public:
    Pair(ExpressionPtr f, ExpressionPtr s);
    const ExpressionPtr &getFirst() const;
    const ExpressionPtr &getSecond() const;

    void accept(Visitor* visitor) const override;
};


#endif //CODE_PAIR_H
