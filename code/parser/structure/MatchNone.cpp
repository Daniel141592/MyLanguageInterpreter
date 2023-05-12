#include "MatchNone.h"

MatchNone::MatchNone(Block::BlockPtr b) : MatchStatement(std::move(b)) {

}

void MatchNone::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
