#ifndef CODE_CONTEXT_H
#define CODE_CONTEXT_H

#include <deque>
#include <string>
#include <variant>

#include "Scope.h"
#include "Variable.h"

class Context {
    std::string currentFunction;
    const std::vector<Expression::ExpressionPtr>* functionArgs{};
    std::deque<Scope> scopes;
public:
    using BlockPtr = Block::BlockPtr;
    Context();
    Context(std::string f);
    std::optional<Variable> findVariable(const std::string& name);
    void addVariable(const std::string& name, const Variable &variable);
    void updateVariable(const std::string& name, double value);
    void updateVariable(const std::string& name, int value);
    void updateVariable(const std::string& name, std::string value);
    void addFunction(const FunctionDeclaration &functionDeclaration);
    const FunctionDeclaration& getFunction(const std::string& name);
    const std::vector<Expression::ExpressionPtr> *getFunctionArgs() const;
    void setFunctionArgs(const std::vector<Expression::ExpressionPtr> *args);

    void addScope();
    void removeScope();
};

#endif //CODE_CONTEXT_H
