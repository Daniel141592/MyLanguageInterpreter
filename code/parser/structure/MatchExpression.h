#ifndef CODE_MATCHEXPRESSION_H
#define CODE_MATCHEXPRESSION_H


#include "MatchStatement.h"
#include "Expression.h"
#include "Identifier.h"

class MatchExpression : public MatchStatement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr expression;
    Identifier identifier;
public:
    MatchExpression(ExpressionPtr e, Identifier id, Block b);
    const ExpressionPtr &getExpression() const;
    const Identifier &getIdentifier() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_MATCHEXPRESSION_H
