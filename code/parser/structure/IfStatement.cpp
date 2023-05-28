#include "IfStatement.h"

const IfStatement::ExpressionPtr &IfStatement::getCondition() const {
    return condition;
}

const Block::BlockPtr &IfStatement::getBlock() const {
    return block;
}

const Block::BlockPtr &IfStatement::getElseBlock() const {
    return elseBlock;
}

IfStatement::IfStatement(IfStatement::ExpressionPtr e, BlockPtr b, BlockPtr elsB) : condition(std::move(e)),
                                        block(std::move(b)), elseBlock(std::move(elsB)) {

}

void IfStatement::accept(Visitor& visitor) const {
    visitor.visit(*this);
}
