#include "FunctionCall.h"

FunctionCall::FunctionCall(Identifier id, std::vector<ExpressionPtr> e)
                                    : Factor(id.getPosition()), name(std::move(id)), args(std::move(e)) {

}

const Identifier &FunctionCall::getName() const {
    return name;
}

const std::vector<FunctionCall::ExpressionPtr> &FunctionCall::getArgs() const {
    return args;
}

void FunctionCall::accept(Visitor& visitor) const {
    visitor.visit(this);
}
