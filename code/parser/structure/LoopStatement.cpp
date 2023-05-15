#include "LoopStatement.h"

LoopStatement::LoopStatement(LoopStatement::ExpressionPtr c, BlockPtr b) : condition(std::move(c)), block(std::move(b)) {

}

const LoopStatement::ExpressionPtr &LoopStatement::getCondition() const {
    return condition;
}

const Block::BlockPtr &LoopStatement::getBlock() const {
    return block;
}

void LoopStatement::accept(Visitor* visitor) const {
    visitor->visit(this);
}
