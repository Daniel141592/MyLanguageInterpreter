#ifndef CODE_PATTERNSTATEMENT_H
#define CODE_PATTERNSTATEMENT_H

#include <optional>
#include <utility>

#include "Statement.h"
#include "Expression.h"
#include "Block.h"
#include "MatchStatement.h"

class PatternStatement : public Statement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr expression;
    std::vector<MatchStatement> matches;
public:
    PatternStatement(ExpressionPtr e, std::vector<MatchStatement> m);
    const ExpressionPtr &getExpression() const;
    const std::vector<MatchStatement> &getMatches() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_PATTERNSTATEMENT_H
