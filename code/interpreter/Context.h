#ifndef CODE_CONTEXT_H
#define CODE_CONTEXT_H

#include <deque>
#include <string>
#include <variant>

#include "Scope.h"
#include "Variable.h"

class Context {
    std::string currentFunction;
    const std::vector<Expression::ExpressionPtr>* functionArgs{};   //TODO można to usunąć jak się dobrze kod przerobi
    std::deque<ScopePtr> scopes;
public:
    using BlockPtr = Block::BlockPtr;
    Context();
    Context(std::string f, ScopePtr scope);
    std::optional<Variable> findVariable(const std::string& name);
    void addVariable(const std::string& name, const Variable &variable);
    void updateVariable(const std::string& name, double value);
    void updateVariable(const std::string& name, int value);
    void updateVariable(const std::string& name, std::string value);
    void addFunction(const FunctionDeclaration &functionDeclaration);
    const FunctionDeclaration& findFunction(const std::string& name);
    const std::vector<Expression::ExpressionPtr> *getFunctionArgs() const;
    void setFunctionArgs(const std::vector<Expression::ExpressionPtr> *args);
    ScopePtr& getGlobalScope();

    void addScope();
    void removeScope();
};

#endif //CODE_CONTEXT_H
