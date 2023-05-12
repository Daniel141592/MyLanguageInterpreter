#ifndef CODE_ASSIGN_H
#define CODE_ASSIGN_H


#include "SingleInstruction.h"
#include "Identifier.h"
#include "Expression.h"

class Assign : public SingleInstruction {
    Identifier identifier;
    std::unique_ptr<Expression> expression;
public:
    Assign(const Identifier& i, std::unique_ptr<Expression> e);
    ~Assign() override = default;

    const Identifier &getIdentifier() const;
    const std::unique_ptr<Expression> &getExpression() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_ASSIGN_H
