#include "ReturnStatement.h"

ReturnStatement::ReturnStatement() = default;

ReturnStatement::ReturnStatement(ReturnStatement::ExpressionPtr e) : expression(std::move(e)) {

}

const ReturnStatement::ExpressionPtr &ReturnStatement::getExpression() const {
    return expression;
}

void ReturnStatement::accept(Visitor& visitor) const {
    visitor.visit(*this);
}
