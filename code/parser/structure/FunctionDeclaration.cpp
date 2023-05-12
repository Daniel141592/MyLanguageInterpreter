#include "FunctionDeclaration.h"

FunctionDeclaration::FunctionDeclaration(Position p, std::string n, Block block)
                    : identifier(p, std::move(n)), functionBody(std::move(block)) {

}

FunctionDeclaration::FunctionDeclaration(Position p, std::string n, Block block, std::vector<Argument> args)
                    : identifier(p, std::move(n)), functionBody(std::move(block)), arguments(std::move(args)) {

}

void FunctionDeclaration::accept(const Visitor *visitor) const {
    visitor->visit(this);
}

const Identifier &FunctionDeclaration::getIdentifier() const {
    return identifier;
}

const std::optional<std::vector<Argument>> &FunctionDeclaration::getArguments() const {
    return arguments;
}

const Block &FunctionDeclaration::getFunctionBody() const {
    return functionBody;
}
