#ifndef CODE_FUNCTIONCALL_H
#define CODE_FUNCTIONCALL_H


#include <vector>
#include "SingleInstruction.h"
#include "Identifier.h"
#include "Expression.h"

class FunctionCall : public SingleInstruction, public Factor {
public:
    using FunctionCallPtr = std::unique_ptr<FunctionCall>;
    using ExpressionPtr = Expression::ExpressionPtr;
private:
    Identifier name;
    std::vector<ExpressionPtr> args;
public:
    FunctionCall(Identifier id, std::vector<ExpressionPtr> e);
    const Identifier &getName() const;
    const std::vector<ExpressionPtr> &getArgs() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_FUNCTIONCALL_H
