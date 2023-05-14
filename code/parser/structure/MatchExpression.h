#ifndef CODE_MATCHEXPRESSION_H
#define CODE_MATCHEXPRESSION_H


#include "MatchStatement.h"
#include "Expression.h"
#include "Identifier.h"

class MatchExpression : public MatchStatement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    using IdentifierPtr = Identifier::IdentifierPtr;
    IdentifierPtr identifier;
    ExpressionPtr expression;
public:
    MatchExpression(ExpressionPtr e, IdentifierPtr id, Block::BlockPtr b);
    const ExpressionPtr &getExpression() const;
    const IdentifierPtr &getIdentifier() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_MATCHEXPRESSION_H
