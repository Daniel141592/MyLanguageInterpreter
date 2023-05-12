#include "IfStatement.h"

const IfStatement::ExpressionPtr &IfStatement::getCondition() const {
    return condition;
}

const Block &IfStatement::getBlock() const {
    return block;
}

const std::optional<Block> &IfStatement::getElseBlock() const {
    return elseBlock;
}

IfStatement::IfStatement(IfStatement::ExpressionPtr e, Block b): condition(std::move(e)), block(std::move(b)) {

}

IfStatement::IfStatement(IfStatement::ExpressionPtr e, Block b, Block elsB) : condition(std::move(e)),
                                        block(std::move(b)), elseBlock(std::move(elsB)) {

}

void IfStatement::accept(const Visitor* visitor) const {
    visitor->visit(this);
}
