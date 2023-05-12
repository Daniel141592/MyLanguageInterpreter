#include "MatchType.h"

MatchType::MatchType(Block::BlockPtr b, IdentifierPtr id) : MatchStatement(std::move(b)), identifier(std::move(id)) {

}

MatchType::MatchType(Block::BlockPtr b, IdentifierPtr id, ConstantType type)
                    : MatchStatement(std::move(b)), identifier(std::move(id)), constantType(type) {

}

const MatchType::IdentifierPtr &MatchType::getIdentifier() const {
    return identifier;
}

const std::optional<ConstantType> &MatchType::getConstantType() const {
    return constantType;
}

void MatchType::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
