#include "LoopStatement.h"

LoopStatement::LoopStatement(LoopStatement::ExpressionPtr c, Block b) : condition(std::move(c)), block(std::move(b)) {

}

const LoopStatement::ExpressionPtr &LoopStatement::getCondition() const {
    return condition;
}

const Block &LoopStatement::getBlock() const {
    return block;
}

void LoopStatement::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
