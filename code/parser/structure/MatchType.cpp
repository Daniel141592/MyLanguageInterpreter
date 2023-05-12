#include "MatchType.h"

MatchType::MatchType(Block b, Identifier id) : MatchStatement(std::move(b)), identifier(std::move(id)) {

}

MatchType::MatchType(Block b, Identifier id, ConstantType type)
                    : MatchStatement(std::move(b)), identifier(std::move(id)), constantType(type) {

}

const Identifier &MatchType::getIdentifier() const {
    return identifier;
}

const std::optional<ConstantType> &MatchType::getConstantType() const {
    return constantType;
}

void MatchType::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
