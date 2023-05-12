#include "ReturnStatement.h"

ReturnStatement::ReturnStatement(ReturnStatement::ExpressionPtr e) : expression(std::move(e)) {

}

const ReturnStatement::ExpressionPtr &ReturnStatement::getExpression() const {
    return expression;
}

void ReturnStatement::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
