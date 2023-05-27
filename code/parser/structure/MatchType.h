#ifndef CODE_MATCHTYPE_H
#define CODE_MATCHTYPE_H


#include <optional>
#include "MatchStatement.h"
#include "ConstantType.h"
#include "Identifier.h"

class MatchType : public MatchStatement {
    using IdentifierPtr = Identifier::IdentifierPtr;
    IdentifierPtr identifier;
    std::optional<ConstantType> constantType;
public:
    MatchType(Block::BlockPtr b, IdentifierPtr id);
    MatchType(Block::BlockPtr b, IdentifierPtr id, ConstantType type);
    const IdentifierPtr &getIdentifier() const;
    const std::optional<ConstantType> &getConstantType() const;

    void accept(Visitor* visitor) const override;
};


#endif //CODE_MATCHTYPE_H
