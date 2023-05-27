#ifndef CODE_VARIABLEDECLARATION_H
#define CODE_VARIABLEDECLARATION_H


#include <optional>
#include "Declaration.h"
#include "Identifier.h"
#include "Expression.h"

class VariableDeclaration : public Declaration {
    using IdentifierPtr = Identifier::IdentifierPtr;
    bool mut;
    IdentifierPtr identifier;
    std::optional<std::unique_ptr<Expression>> expression;
public:
    explicit VariableDeclaration(IdentifierPtr i, bool m = false);
    VariableDeclaration(IdentifierPtr i, std::unique_ptr<Expression> e, bool m = false);

    bool isMut() const;
    const IdentifierPtr& getIdentifier() const;
    const std::optional<std::unique_ptr<Expression>> &getExpression() const;


    void accept(Visitor& visitor) const override;
};


#endif //CODE_VARIABLEDECLARATION_H
