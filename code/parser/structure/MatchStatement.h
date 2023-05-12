#ifndef CODE_MATCHSTATEMENT_H
#define CODE_MATCHSTATEMENT_H


#include "Statement.h"
#include "Block.h"

class MatchStatement : public Statement {
public:
    using MatchStatementPtr = std::unique_ptr<MatchStatement>;
    using BlockPtr = Block::BlockPtr;
private:
    BlockPtr block;
public:
    MatchStatement(BlockPtr b);
    const BlockPtr &getBlock() const;

    void accept(const Visitor *visitor) const override = 0;
};


#endif //CODE_MATCHSTATEMENT_H
