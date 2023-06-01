#include "Scope.h"

Scope::Scope() = default;

Scope::Scope(std::unordered_map<std::string, Variable> vars,
             std::unordered_map<std::string, const FunctionDeclaration&> funcs)
                                                        : variables(std::move(vars)), functions(std::move(funcs)) {

}

std::unordered_map<std::string, Variable> &Scope::getVariables() {
    return variables;
}

std::unordered_map<std::string, const FunctionDeclaration&> &Scope::getFunctions() {
    return functions;
}

bool Scope::variableDeclared(const std::string &name) {
    auto vit = variables.find(name);
    if (vit != variables.end())
        return true;
    return false;
}

void Scope::addVariable(const std::string &name, const Variable &variable) {
    variables.insert(std::make_pair(name, variable));
}
