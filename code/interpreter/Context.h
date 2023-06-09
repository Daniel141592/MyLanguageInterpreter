#ifndef CODE_CONTEXT_H
#define CODE_CONTEXT_H

#include <deque>
#include <string>
#include <variant>

#include "Scope.h"
#include "Variable.h"
#include "Exceptions.h"

class Context {
    std::string currentFunction;
    std::deque<ScopePtr> scopes;
public:
    using BlockPtr = Block::BlockPtr;
    Context();
    Context(std::string f, ScopePtr globalScope, ScopePtr newScope);
    std::optional<Variable> findVariable(const std::string& name);
    void addVariable(const std::string& name, const Variable &variable);
    void addFunction(const FunctionDeclaration &functionDeclaration);
    const FunctionDeclaration& findFunction(const std::string& name);
    ScopePtr& getGlobalScope();
    bool variableDeclaredInCurrentScope(const std::string& name);
    void addScope();
    void removeScope();
    const std::optional<Value> &getMatching() const;
    void setMatching(const std::optional<Value> &matching);
    void endMatching();

    template<typename T>
    VariableType getExpectedType();

    template<typename T>
    void updateVariable(const std::string &name, const T &value) {
        for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
            auto vit = (*sit)->getVariables().find(name);
            if (vit != (*sit)->getVariables().end()) {
                if (vit->second.getType() && vit->second.getType().value() != getExpectedType<T>())
                    throw IncompatibleTypeException(vit->second.getType().value(), getExpectedType<T>());
                if (!vit->second.isMut())
                    throw ReassignImmutableVariableException(name);
                vit->second.setValue(value);
                return;
            }
        }
        addVariable(name, Variable(value, false));
    }
};

#endif //CODE_CONTEXT_H
