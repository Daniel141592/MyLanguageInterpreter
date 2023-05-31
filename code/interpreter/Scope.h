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
public:
    Scope();
    Scope(std::unordered_map<std::string, Variable> vars,
          std::unordered_map<std::string, const FunctionDeclaration&> funcs);

    std::unordered_map<std::string, Variable> &getVariables();
    std::unordered_map<std::string, const FunctionDeclaration&> &getFunctions();
};


#endif //CODE_SCOPE_H
