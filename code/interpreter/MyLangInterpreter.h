#ifndef CODE_MYLANGINTERPRETER_H
#define CODE_MYLANGINTERPRETER_H

#include <functional>
#include <utility>

#include "Interpreter.h"
#include "../Visitor.h"
#include "../structure/FunctionDeclaration.h"
#include "../structure/Statement.h"
#include "../structure/SingleInstruction.h"
#include "../structure/Block.h"
#include "../structure/Declaration.h"
#include "../structure/VariableDeclaration.h"
#include "../structure/FunctionCall.h"
#include "../structure/Identifier.h"
#include "../structure/Assign.h"
#include "../structure/IfStatement.h"
#include "../structure/LoopStatement.h"
#include "../structure/PatternStatement.h"
#include "../structure/ReturnStatement.h"
#include "../structure/MatchStatement.h"
#include "../structure/MatchNone.h"
#include "../structure/MatchType.h"
#include "../structure/MatchPair.h"
#include "../structure/MatchExpression.h"
#include "../structure/OrExpression.h"
#include "../structure/AndExpression.h"
#include "../structure/RelativeExpression.h"
#include "../structure/AdditiveExpression.h"
#include "../structure/MultiplicationExpression.h"
#include "../structure/NegatedExpression.h"
#include "../structure/CastExpression.h"
#include "../structure/Constant.h"
#include "../structure/Field.h"
#include "../structure/ConstantType.h"
#include "../structure/Pair.h"
#include "../structure/Typename.h"
#include "../structure/StandardOutput.h"
#include "Context.h"
#include "Variable.h"
#include "Value.h"

class MyLangInterpreter : public Interpreter, public Visitor {
    std::ostream& os;
    std::istream& is;
    HandlerType errorHandler;
    std::deque<Context> contexts;
    Value result;
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
    void visit(const StandardOutput &standardOutput) override;

    void execute(const Program& program) override;
private:
    void criticalError(ErrorType type);
};

#endif //CODE_MYLANGINTERPRETER_H
