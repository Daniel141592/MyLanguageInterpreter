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
private:
    ExpressionPtr condition;
    Block block;
    std::optional<Block> elseBlock;
public:
    IfStatement(ExpressionPtr e, Block  b);
    IfStatement(ExpressionPtr e, Block b, Block elsB);

    const ExpressionPtr &getCondition() const;
    const Block &getBlock() const;
    const std::optional<Block> &getElseBlock() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_IFSTATEMENT_H
