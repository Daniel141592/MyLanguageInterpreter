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
    Identifier identifier;
    std::optional<std::vector<Argument>> arguments;
    Block functionBody;
public:
    FunctionDeclaration(std::string n, Block block);
    FunctionDeclaration(std::string n, Block block, std::vector<Argument> args);

    const Identifier &getIdentifier() const;

    const std::optional<std::vector<Argument>> &getArguments() const;

    const Block &getFunctionBody() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_FUNCTIONDECLARATION_H
