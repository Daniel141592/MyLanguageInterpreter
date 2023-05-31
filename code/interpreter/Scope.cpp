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
