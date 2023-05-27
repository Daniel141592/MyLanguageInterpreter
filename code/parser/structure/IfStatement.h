#ifndef CODE_IFSTATEMENT_H
#define CODE_IFSTATEMENT_H


#include <optional>
#include <utility>

#include "Statement.h"
#include "Expression.h"
#include "Block.h"

class IfStatement : public Statement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
    using BlockPtr = Block::BlockPtr;
private:
    ExpressionPtr condition;
    BlockPtr block;
    BlockPtr elseBlock;
public:
    IfStatement(ExpressionPtr e, BlockPtr b);
    IfStatement(ExpressionPtr e, BlockPtr b, BlockPtr elsB);

    const ExpressionPtr &getCondition() const;
    const BlockPtr &getBlock() const;
    const BlockPtr &getElseBlock() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_IFSTATEMENT_H
