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
private:
    ExpressionPtr condition;
    Block block;
public:
    LoopStatement(ExpressionPtr c, Block b);
    const ExpressionPtr &getCondition() const;
    const Block &getBlock() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_LOOPSTATEMENT_H
