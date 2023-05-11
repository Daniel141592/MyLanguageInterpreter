#ifndef CODE_PRINTVISITOR_H
#define CODE_PRINTVISITOR_H

#include <iostream>

#include "Visitor.h"
#include "structure/Program.h"
#include "structure/Block.h"
#include "structure/OrExpression.h"
#include "structure/VariableDeclaration.h"
#include "structure/FunctionDeclaration.h"
#include "structure/Argument.h"
#include "structure/Assign.h"

class PrintVisitor : public Visitor {
public:
    PrintVisitor();
    ~PrintVisitor() override = default;

    void visit(const Program* program) const override;
    void visit(const Block* block) const override;
    void visit(const OrExpression* expression) const override;
    void visit(const VariableDeclaration* variableDeclaration) const override;
    void visit(const FunctionDeclaration* functionDeclaration) const override;
    void visit(const Identifier* identifier) const override;
    void visit(const Argument* argument) const override;
    void visit(const Assign* assign) const override;
};


#endif //CODE_PRINTVISITOR_H
