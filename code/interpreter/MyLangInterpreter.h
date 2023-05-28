#ifndef CODE_MYLANGINTERPRETER_H
#define CODE_MYLANGINTERPRETER_H

#include <functional>
#include <utility>

#include "Interpreter.h"
#include "../Visitor.h"
#include "../structure/Program.h"

class MyLangInterpreter : public Interpreter, public Visitor {
    std::ostream& os;
    std::istream& is;
    HandlerType errorHandler;
public:
    MyLangInterpreter(std::ostream& o, std::istream& i, HandlerType onError);
    ~MyLangInterpreter() override = default;

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

    void execute(const Program& program) override;
};

#endif //CODE_MYLANGINTERPRETER_H
