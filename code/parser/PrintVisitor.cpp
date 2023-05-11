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
    // TODO jakiś print
    expression->getLeft()->accept(this);
    expression->getRight()->accept(this);
}

void PrintVisitor::visit(const VariableDeclaration* variableDeclaration) const {
    variableDeclaration->isMut();
    if (variableDeclaration->getExpression())
        variableDeclaration->getExpression()->get()->accept(this);
    variableDeclaration->getIdentifier().accept(this);
}

void PrintVisitor::visit(const FunctionDeclaration* functionDeclaration) const {
    std::cout << "function: " << functionDeclaration->getIdentifier().getName() << '\n';
    if (functionDeclaration->getArguments()) {
        std::cout << "\targuments:\n";
        for (auto &arg : *functionDeclaration->getArguments())
            arg.accept(this);
    }
    std::cout << "\tbody:\n";
    functionDeclaration->getFunctionBody().accept(this);
}

void PrintVisitor::visit(const Identifier* identifier) const {
    std::cout << identifier->getName() << '\n';
}

void PrintVisitor::visit(const Argument* argument) const {
    std::cout << "argument: " ;
    argument->getIdentifier().accept(this);
}

void PrintVisitor::visit(const Assign* assign) const {
    std::cout << "assign: " << assign->getIdentifier().getName() << '\n';
    assign->getExpression()->accept(this);
}


