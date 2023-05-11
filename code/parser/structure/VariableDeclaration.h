#ifndef CODE_VARIABLEDECLARATION_H
#define CODE_VARIABLEDECLARATION_H


#include <optional>
#include "Declaration.h"
#include "Identifier.h"
#include "Expression.h"

class VariableDeclaration : public Declaration {
    bool mut;
    Identifier identifier;
    std::optional<std::unique_ptr<Expression>> expression;
public:
    VariableDeclaration(const Identifier& i, bool m = false);
    VariableDeclaration(const Identifier& i, std::unique_ptr<Expression> e, bool m = false);

    bool isMut() const;
    const Identifier &getIdentifier() const;
    const std::optional<std::unique_ptr<Expression>> &getExpression() const;


    void accept(const Visitor* visitor) const override;
};


#endif //CODE_VARIABLEDECLARATION_H
