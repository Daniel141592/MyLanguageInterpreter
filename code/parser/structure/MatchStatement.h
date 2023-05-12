#ifndef CODE_MATCHSTATEMENT_H
#define CODE_MATCHSTATEMENT_H


#include "Statement.h"
#include "Block.h"

class MatchStatement : public Statement {
    Block block;
public:
    MatchStatement(Block b);
    const Block &getBlock() const;

    void accept(const Visitor *visitor) const override = 0;
};


#endif //CODE_MATCHSTATEMENT_H
