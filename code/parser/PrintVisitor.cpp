#include "PrintVisitor.h"

PrintVisitor::PrintVisitor() = default;

void PrintVisitor::visit(const Program* program) const {
    for (auto &ins : program->getInstructions()) {
        ins->accept(this);
    }
}

void PrintVisitor::visit(const Block* block) const {
    for (auto &ins : block->getInstructions()) {
        ins->accept(this);
    }
}

void PrintVisitor::visit(const OrExpression* expression) const {
    std::cout << "or expression\n";
    expression->getLeft()->accept(this);
    expression->getRight()->accept(this);
}

void PrintVisitor::visit(const AndExpression* andExpression) const {
    std::cout << "and expression\n";
    andExpression->getLeft()->accept(this);
    andExpression->getRight()->accept(this);
}

void PrintVisitor::visit(const VariableDeclaration* variableDeclaration) const {
    variableDeclaration->isMut();
    if (variableDeclaration->getExpression())
        variableDeclaration->getExpression()->get()->accept(this);
    variableDeclaration->getIdentifier()->accept(this);
}

void PrintVisitor::visit(const FunctionDeclaration* functionDeclaration) const {
    std::cout << "function: " << functionDeclaration->getIdentifier().getName() << '\n';
    if (functionDeclaration->getArguments()) {
        std::cout << "\targuments:\n";
        for (auto &arg : *functionDeclaration->getArguments())
            arg.accept(this);
    }
    std::cout << "\tbody:\n";
    functionDeclaration->getFunctionBody()->accept(this);
}

void PrintVisitor::visit(const Identifier* identifier) const {
    std::cout << identifier->getName() << '\n';
}

void PrintVisitor::visit(const Argument* argument) const {
    std::cout << "argument: " ;
    argument->getIdentifier().accept(this);
}

void PrintVisitor::visit(const Assign* assign) const {
    std::cout << "assign: " << assign->getIdentifier()->getName() << '\n';
    assign->getExpression()->accept(this);
}

void PrintVisitor::visit(const IfStatement *ifStatement) const {
    std::cout << "if\n";
    ifStatement->getCondition()->accept(this);
    ifStatement->getBlock()->accept(this);
    if (ifStatement->getElseBlock())
        ifStatement->getElseBlock().value()->accept(this);
}

void PrintVisitor::visit(const LoopStatement *loopStatement) const {
    std::cout << "loop\n";
    loopStatement->getCondition()->accept(this);
    loopStatement->getBlock()->accept(this);
}

void PrintVisitor::visit(const PatternStatement *patternStatement) const {
    std::cout << "pattern\n";
    patternStatement->getExpression()->accept(this);
    for (auto &m : patternStatement->getMatches()) {
        m->accept(this);
    }
}

void PrintVisitor::visit(const ReturnStatement *returnStatement) const {
    std::cout << "return\n";
    returnStatement->getExpression()->accept(this);
}

void PrintVisitor::visit(const FunctionCall *functionCall) const {
    std::cout << "function call: ";
    functionCall->getName().accept(this);
    std::cout << "args:\n";
    for (auto &arg : functionCall->getArgs()) {
        arg->accept(this);
    }
}

void PrintVisitor::visit(const RelativeExpression *relativeExpression) const {
    std::cout << "relative expression, type: <#TODO>\n";
    relativeExpression->getRelativeType();
    relativeExpression->getLeft()->accept(this);
    relativeExpression->getRight()->accept(this);
    relativeExpression->getPosition();
}

void PrintVisitor::visit(const AdditiveExpression *additiveExpression) const {
    std::cout << (additiveExpression->getAdditiveType() == AdditiveType::ADD ? "add" : "subtract") << " expression\n";
    additiveExpression->getLeft()->accept(this);
    additiveExpression->getRight()->accept(this);
}

void PrintVisitor::visit(const MultiplicationExpression *multiplicationExpression) const {
    std::cout << "multiplication expression, type <#TODO>\n";
    multiplicationExpression->getLeft()->accept(this);
    multiplicationExpression->getRight()->accept(this);
}

void PrintVisitor::visit(const Constant *constant) const {
    if (constant->getConstantType() == ConstantType::INTEGER)
        std::cout << "integer constant: " << std::get<int>(constant->getValue()) << '\n';
    else if (constant->getConstantType() == ConstantType::FLOAT)
        std::cout << "float constant: " << std::get<double>(constant->getValue()) << '\n';
    else
        std::cout << "string constant: " << std::get<std::string>(constant->getValue()) << '\n';
}

void PrintVisitor::visit(const Field *field) const {
    std::cout << "field: " << (field->getFieldType() == FieldType::FIRST ? ".first" : ".second") << '\n';
    field->getExpression()->accept(this);
}

void PrintVisitor::visit(const CastExpression *castExpression) const {
    std::cout << "cast expression, type: ";
    if (castExpression->getType() == ConstantType::INTEGER)
        std::cout << "integer\n";
    else if (castExpression->getType() == ConstantType::FLOAT)
        std::cout << "float\n";
    else
        std::cout << "string\n";
    castExpression->getExpression()->accept(this);
}

void PrintVisitor::visit(const NegatedExpression *negatedExpression) const {
    std::cout << "negated expression: ";
    negatedExpression->getExpression()->accept(this);
}

void PrintVisitor::visit(const MatchExpression *matchExpression) const {
    std::cout << "match expression: \n";
    matchExpression->getExpression()->accept(this);
    std::cout << "id: ";
    matchExpression->getIdentifier().accept(this);
    matchExpression->getBlock()->accept(this);
}

void PrintVisitor::visit(const MatchPair *matchPair) const {
    std::cout << "match pair: \n";
    std::cout << "first: ";
    matchPair->getFirst()->accept(this);
    std::cout << "second: ";
    matchPair->getSecond()->accept(this);
    matchPair->getBlock()->accept(this);
}

void PrintVisitor::visit(const MatchType *matchType) const {
    std::cout << "match ";
    if (!matchType->getConstantType())
        std::cout << " everything\n";
    else if (matchType->getConstantType() == ConstantType::INTEGER)
        std::cout << "integer\n";
    else if (matchType->getConstantType() == ConstantType::FLOAT)
        std::cout << "float\n";
    else
        std::cout << "string\n";
    matchType->getIdentifier()->accept(this);
    matchType->getBlock()->accept(this);
}

void PrintVisitor::visit(const MatchNone *matchNone) const {
    std::cout << "match none\n";
    matchNone->getBlock()->accept(this);
}


