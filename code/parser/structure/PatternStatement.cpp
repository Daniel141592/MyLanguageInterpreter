#include "PatternStatement.h"

PatternStatement::PatternStatement(PatternStatement::ExpressionPtr e, std::vector<MatchStatementPtr> m)
                                                        : expression(std::move(e)), matches(std::move(m)) {

}

const PatternStatement::ExpressionPtr &PatternStatement::getExpression() const {
    return expression;
}

const std::vector<MatchStatement::MatchStatementPtr> &PatternStatement::getMatches() const {
    return matches;
}

void PatternStatement::accept(const Visitor *visitor) const {
    visitor->visit(this);
}

