#ifndef CODE_MATCHNONE_H
#define CODE_MATCHNONE_H

#include "MatchStatement.h"

class MatchNone : public MatchStatement {
public:
    MatchNone(Block::BlockPtr b);

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_MATCHNONE_H
