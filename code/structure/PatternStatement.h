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
    using MatchStatementPtr = MatchStatement::MatchStatementPtr;
private:
    ExpressionPtr expression;
    std::vector<MatchStatementPtr> matches;
public:
    PatternStatement(ExpressionPtr e, std::vector<MatchStatementPtr> m);
    const ExpressionPtr &getExpression() const;
    const std::vector<MatchStatementPtr> &getMatches() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_PATTERNSTATEMENT_H
