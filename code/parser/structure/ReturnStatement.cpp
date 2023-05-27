#include "ReturnStatement.h"

ReturnStatement::ReturnStatement() : expression({}) {

}

ReturnStatement::ReturnStatement(ReturnStatement::ExpressionPtr e) : expression(std::move(e)) {

}

const std::optional<ReturnStatement::ExpressionPtr> &ReturnStatement::getExpression() const {
    return expression;
}

void ReturnStatement::accept(Visitor& visitor) const {
    visitor.visit(this);
}
