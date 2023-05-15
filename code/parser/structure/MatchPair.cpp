#include "MatchPair.h"

MatchPair::MatchPair(Block::BlockPtr b, MatchPair::ExpressionPtr f, MatchPair::ExpressionPtr s)
                        : MatchStatement(std::move(b)), first(std::move(f)), second(std::move(s)) {

}

const MatchPair::ExpressionPtr &MatchPair::getFirst() const {
    return first;
}

const MatchPair::ExpressionPtr &MatchPair::getSecond() const {
    return second;
}

void MatchPair::accept(Visitor* visitor) const {
    visitor->visit(this);
}
