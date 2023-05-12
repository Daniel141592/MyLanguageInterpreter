#ifndef CODE_FUNCTIONDECLARATION_H
#define CODE_FUNCTIONDECLARATION_H


#include <optional>
#include <vector>
#include <utility>

#include "Declaration.h"
#include "Argument.h"
#include "Block.h"
#include "Identifier.h"

class FunctionDeclaration : public Declaration {
    using BlockPtr = Block::BlockPtr;
    Identifier identifier;
    std::optional<std::vector<Argument>> arguments;
    BlockPtr functionBody;
public:
    FunctionDeclaration(Position p, std::string n, BlockPtr block);
    FunctionDeclaration(Position p, std::string n, BlockPtr block, std::vector<Argument> args);

    const Identifier &getIdentifier() const;
    const std::optional<std::vector<Argument>> &getArguments() const;
    const BlockPtr &getFunctionBody() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_FUNCTIONDECLARATION_H
