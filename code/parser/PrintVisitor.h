#ifndef CODE_PRINTVISITOR_H
#define CODE_PRINTVISITOR_H

#include <iostream>

#include "Visitor.h"
#include "structure/Program.h"
#include "structure/Block.h"
#include "structure/OrExpression.h"
#include "structure/AndExpression.h"
#include "structure/VariableDeclaration.h"
#include "structure/FunctionDeclaration.h"
#include "structure/Argument.h"
#include "structure/Assign.h"
#include "structure/IfStatement.h"
#include "structure/LoopStatement.h"
#include "structure/PatternStatement.h"
#include "structure/ReturnStatement.h"
#include "structure/FunctionCall.h"
#include "structure/RelativeExpression.h"
#include "structure/AdditiveExpression.h"
#include "structure/MultiplicationExpression.h"
#include "structure/Constant.h"
#include "structure/Field.h"
#include "structure/CastExpression.h"
#include "structure/NegatedExpression.h"
#include "structure/MatchExpression.h"
#include "structure/MatchPair.h"
#include "structure/MatchType.h"
#include "structure/MatchNone.h"

class PrintVisitor : public Visitor {
public:
    PrintVisitor();
    ~PrintVisitor() override = default;

    void visit(const Program* program) const override;
    void visit(const Block* block) const override;
    void visit(const OrExpression* orExpression) const override;
    void visit(const AndExpression* andExpression) const override;
    void visit(const VariableDeclaration* variableDeclaration) const override;
    void visit(const FunctionDeclaration* functionDeclaration) const override;
    void visit(const Identifier* identifier) const override;
    void visit(const Argument* argument) const override;
    void visit(const Assign* assign) const override;
    void visit(const IfStatement* ifStatement) const override;
    void visit(const LoopStatement* loopStatement) const override;
    void visit(const PatternStatement* patternStatement) const override;
    void visit(const ReturnStatement* returnStatement) const override;
    void visit(const FunctionCall* functionCall) const override;
    void visit(const RelativeExpression* relativeExpression) const override;
    void visit(const AdditiveExpression* additiveExpression) const override;
    void visit(const MultiplicationExpression* multiplicationExpression) const override;
    void visit(const Constant* constant) const override;
    void visit(const Field* field) const override;
    void visit(const CastExpression* castExpression) const override;
    void visit(const NegatedExpression* negatedExpression) const override;
    void visit(const MatchExpression* matchExpression) const override;
    void visit(const MatchPair* matchPair) const override;
    void visit(const MatchType* matchType) const override;
    void visit(const MatchNone* matchNone) const override;
};


#endif //CODE_PRINTVISITOR_H
