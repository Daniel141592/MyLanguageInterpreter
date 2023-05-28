#include "MatchNone.h"

MatchNone::MatchNone(Block::BlockPtr b) : MatchStatement(std::move(b)) {

}

void MatchNone::accept(Visitor& visitor) const {
    visitor.visit(*this);
}
