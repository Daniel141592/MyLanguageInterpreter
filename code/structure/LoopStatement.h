#ifndef CODE_LOOPSTATEMENT_H
#define CODE_LOOPSTATEMENT_H

#include <optional>
#include <utility>

#include "Statement.h"
#include "Expression.h"
#include "Block.h"

class LoopStatement : public Statement {
public:
    using ExpressionPtr = Expression::ExpressionPtr;
    using BlockPtr = Block::BlockPtr;
private:
    ExpressionPtr condition;
    BlockPtr block;
public:
    LoopStatement(ExpressionPtr c, BlockPtr b);
    const ExpressionPtr &getCondition() const;
    const BlockPtr &getBlock() const;

    void accept(Visitor& visitor) const override;
};


#endif //CODE_LOOPSTATEMENT_H
