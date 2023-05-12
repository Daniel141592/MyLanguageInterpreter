#ifndef CODE_MATCHPAIR_H
#define CODE_MATCHPAIR_H

#include "Expression.h"
#include "MatchStatement.h"

class MatchPair : public MatchStatement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr first;
    ExpressionPtr second;
public:
    MatchPair(Block b, ExpressionPtr f, ExpressionPtr s);
    const ExpressionPtr &getFirst() const;
    const ExpressionPtr &getSecond() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_MATCHPAIR_H
