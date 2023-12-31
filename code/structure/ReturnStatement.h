#ifndef CODE_RETURNSTATEMENT_H
#define CODE_RETURNSTATEMENT_H

#include <optional>
#include "Statement.h"
#include "Expression.h"

class ReturnStatement : public Statement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    ExpressionPtr expression;
public:
    ReturnStatement();
    explicit ReturnStatement(ExpressionPtr e);
    const ExpressionPtr &getExpression() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_RETURNSTATEMENT_H
