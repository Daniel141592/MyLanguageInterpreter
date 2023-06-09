#ifndef CODE_PRINTVISITOR_H
#define CODE_PRINTVISITOR_H

#include <iostream>
#include <functional>
#include <sstream>

#include "../Visitor.h"
#include "../structure/Program.h"
#include "../structure/Block.h"
#include "../structure/OrExpression.h"
#include "../structure/AndExpression.h"
#include "../structure/VariableDeclaration.h"
#include "../structure/FunctionDeclaration.h"
#include "../structure/Argument.h"
#include "../structure/Assign.h"
#include "../structure/IfStatement.h"
#include "../structure/LoopStatement.h"
#include "../structure/PatternStatement.h"
#include "../structure/ReturnStatement.h"
#include "../structure/FunctionCall.h"
#include "../structure/RelativeExpression.h"
#include "../structure/AdditiveExpression.h"
#include "../structure/MultiplicationExpression.h"
#include "../structure/Constant.h"
#include "../structure/Field.h"
#include "../structure/CastExpression.h"
#include "../structure/NegatedExpression.h"
#include "../structure/MatchExpression.h"
#include "../structure/MatchPair.h"
#include "../structure/MatchType.h"
#include "../structure/MatchNone.h"
#include "../structure/Pair.h"
#include "../structure/Typename.h"
#include "../structure/StandardOutput.h"

class PrintVisitor : public Visitor {
    int indent;
    std::ostream& output;
public:
    PrintVisitor();
    explicit PrintVisitor(std::ostream& os);
    ~PrintVisitor() override = default;

    void visit(const Program& program) override;
    void visit(const Block& block) override;
    void visit(const OrExpression& orExpression) override;
    void visit(const AndExpression& andExpression) override;
    void visit(const VariableDeclaration& variableDeclaration) override;
    void visit(const FunctionDeclaration& functionDeclaration) override;
    void visit(const Identifier& identifier) override;
    void visit(const Argument& argument) override;
    void visit(const Assign& assign) override;
    void visit(const IfStatement& ifStatement) override;
    void visit(const LoopStatement& loopStatement) override;
    void visit(const PatternStatement& patternStatement) override;
    void visit(const ReturnStatement& returnStatement) override;
    void visit(const FunctionCall& functionCall) override;
    void visit(const RelativeExpression& relativeExpression) override;
    void visit(const AdditiveExpression& additiveExpression) override;
    void visit(const MultiplicationExpression& multiplicationExpression) override;
    void visit(const Constant& constant) override;
    void visit(const Field& field) override;
    void visit(const CastExpression& castExpression) override;
    void visit(const NegatedExpression& negatedExpression) override;
    void visit(const MatchExpression& matchExpression) override;
    void visit(const MatchPair& matchPair) override;
    void visit(const MatchType& matchType) override;
    void visit(const MatchNone& matchNone) override;
    void visit(const Pair& pair) override;
    void visit(const Typename& type) override;
    void visit(const StandardOutput& standardOutput) override;
private:
    void print(const char* str) const;
    void manageIndent(const std::function<void()>& lambda);
};


#endif //CODE_PRINTVISITOR_H
