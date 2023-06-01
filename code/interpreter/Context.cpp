#include "Context.h"
#include "Value.h"

Context::Context() = default;

Context::Context(std::string f, ScopePtr globalScope, ScopePtr newScope) : currentFunction(std::move(f)) {
    scopes.emplace_back(std::move(globalScope));
    scopes.emplace_back(std::move(newScope));
}

std::optional<Variable> Context::findVariable(const std::string& name) {
    for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
        auto vit = (*sit)->getVariables().find(name);
        if (vit != (*sit)->getVariables().end())
            return vit->second;
    }
    return {};
}

void Context::addVariable(const std::string& name, const Variable &variable) {
    scopes.back()->addVariable(name, variable);
}

void Context::updateVariable(const std::string &name, int value) {
    for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
        auto vit = (*sit)->getVariables().find(name);
        if (vit != (*sit)->getVariables().end()) {
            if (vit->second.getType() != ConstantType::INTEGER)
                throw IncompatibleTypeException(vit->second.getType(), ConstantType::INTEGER);
            if (!vit->second.isMut())
                throw ReassignImmutableVariable(name);
            vit->second.setValue(value);
            return;
        }
    }
    addVariable(name, Variable(value, false));
}

void Context::updateVariable(const std::string& name, double value) {
    for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
        auto vit = (*sit)->getVariables().find(name);
        if (vit != (*sit)->getVariables().end()) {
            if (vit->second.getType() != ConstantType::FLOAT)
                throw IncompatibleTypeException(vit->second.getType(), ConstantType::FLOAT);
            if (!vit->second.isMut())
                throw ReassignImmutableVariable(name);
            vit->second.setValue(value);
            return;
        }
    }
    addVariable(name, Variable(value, false));
}

void Context::updateVariable(const std::string& name, std::string value) {
    for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
        auto vit = (*sit)->getVariables().find(name);
        if (vit != (*sit)->getVariables().end()) {
            if (vit->second.getType() != ConstantType::STRING)
                throw IncompatibleTypeException(vit->second.getType(), ConstantType::STRING);
            if (!vit->second.isMut())
                throw ReassignImmutableVariable(name);
            vit->second.setValue(value);
            return;
        }
    }
    addVariable(name, Variable(value, false));
}

void Context::addScope() {
    scopes.emplace_back(std::make_shared<Scope>());
}

void Context::removeScope() {
    scopes.pop_back();
}

void Context::addFunction(const FunctionDeclaration &functionDeclaration) {
    scopes.back()->getFunctions().insert(
            std::make_pair(functionDeclaration.getIdentifier().getName(), std::ref(functionDeclaration)));
}

const FunctionDeclaration &Context::findFunction(const std::string &name) {
    for (auto sit = scopes.rbegin(); sit != scopes.rend(); ++sit) {
        auto fit = (*sit)->getFunctions().find(name);
        if (fit != scopes.back()->getFunctions().end())
            return fit->second;
    }
    throw UnknownIdentifierException(name);
}

const std::vector<Expression::ExpressionPtr> *Context::getFunctionArgs() const {
    return functionArgs;
}

void Context::setFunctionArgs(const std::vector<Expression::ExpressionPtr> *args) {
    functionArgs = args;
}

ScopePtr& Context::getGlobalScope() {
    return scopes.front();
}

bool Context::variableDeclaredInCurrentScope(const std::string &name) {
    return scopes.back()->variableDeclared(name);
}
