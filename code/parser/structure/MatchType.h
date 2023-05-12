#ifndef CODE_MATCHTYPE_H
#define CODE_MATCHTYPE_H


#include <optional>
#include "MatchStatement.h"
#include "ConstantType.h"
#include "Identifier.h"

class MatchType : public MatchStatement {
    Identifier identifier;
    std::optional<ConstantType> constantType;
public:
    MatchType(Block b, Identifier id);
    MatchType(Block b, Identifier id, ConstantType type);
    const Identifier &getIdentifier() const;
    const std::optional<ConstantType> &getConstantType() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_MATCHTYPE_H
