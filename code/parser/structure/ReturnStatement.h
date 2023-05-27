#ifndef CODE_RETURNSTATEMENT_H
#define CODE_RETURNSTATEMENT_H

#include <optional>
#include "Statement.h"
#include "Expression.h"

class ReturnStatement : public Statement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    std::optional<ExpressionPtr> expression;
public:
    ReturnStatement();
    ReturnStatement(ExpressionPtr e);
    const std::optional<ExpressionPtr> &getExpression() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_RETURNSTATEMENT_H
