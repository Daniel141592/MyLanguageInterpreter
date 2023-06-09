#ifndef CODE_SCOPE_H
#define CODE_SCOPE_H

#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include "Variable.h"
#include "../structure/FunctionDeclaration.h"

class Scope {
    std::unordered_map<std::string, Variable> variables;
    std::unordered_map<std::string, const FunctionDeclaration&> functions;
    std::optional<Value> matching;
public:
    Scope();
    Scope(std::unordered_map<std::string, Variable> vars,
          std::unordered_map<std::string, const FunctionDeclaration&> funcs);

    std::unordered_map<std::string, Variable> &getVariables();
    std::unordered_map<std::string, const FunctionDeclaration&> &getFunctions();
    bool variableDeclared(const std::string& name);
    void addVariable(const std::string& name, const Variable &variable);
    const std::optional<Value> &getMatching() const;
    void setMatching(const std::optional<Value> &matching);
};
using ScopePtr = std::shared_ptr<Scope>;

#endif //CODE_SCOPE_H
