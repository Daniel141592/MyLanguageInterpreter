#include "FunctionCall.h"

FunctionCall::FunctionCall(Position p, Identifier id, std::vector<ExpressionPtr> e)
                                    : Factor(p), name(std::move(id)), args(std::move(e)) {

}

const Identifier &FunctionCall::getName() const {
    return name;
}

const std::vector<FunctionCall::ExpressionPtr> &FunctionCall::getArgs() const {
    return args;
}

void FunctionCall::accept(const Visitor *visitor) const {
    visitor->visit(this);
}
