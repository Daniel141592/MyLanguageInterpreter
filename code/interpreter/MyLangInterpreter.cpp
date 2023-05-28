#include "MyLangInterpreter.h"
#include "Variable.h"

MyLangInterpreter::MyLangInterpreter(std::ostream &o, std::istream &i, Interpreter::HandlerType onError)
                                                                    : os(o), is(i), errorHandler(std::move(onError)) {

}

void MyLangInterpreter::execute(const Program &program) {
    visit(program);
}

void MyLangInterpreter::visit(const Program &program) {
    std::vector<Variable> variables;
    for (auto &ins: program.getInstructions()) {
        ins->accept(*this);
    }
}

void MyLangInterpreter::visit(const Block &block) {

}

void MyLangInterpreter::visit(const OrExpression &orExpression) {

}

void MyLangInterpreter::visit(const AndExpression &andExpression) {

}

void MyLangInterpreter::visit(const VariableDeclaration &variableDeclaration) {

}

void MyLangInterpreter::visit(const FunctionDeclaration &functionDeclaration) {

}

void MyLangInterpreter::visit(const Identifier &identifier) {

}

void MyLangInterpreter::visit(const Argument &argument) {

}

void MyLangInterpreter::visit(const Assign &assign) {

}

void MyLangInterpreter::visit(const IfStatement &ifStatement) {

}

void MyLangInterpreter::visit(const LoopStatement &loopStatement) {

}

void MyLangInterpreter::visit(const PatternStatement &patternStatement) {

}

void MyLangInterpreter::visit(const ReturnStatement &returnStatement) {

}

void MyLangInterpreter::visit(const FunctionCall &functionCall) {

}

void MyLangInterpreter::visit(const RelativeExpression &relativeExpression) {

}

void MyLangInterpreter::visit(const AdditiveExpression &additiveExpression) {

}

void MyLangInterpreter::visit(const MultiplicationExpression &multiplicationExpression) {

}

void MyLangInterpreter::visit(const Constant &constant) {

}

void MyLangInterpreter::visit(const Field &field) {

}

void MyLangInterpreter::visit(const CastExpression &castExpression) {

}

void MyLangInterpreter::visit(const NegatedExpression &negatedExpression) {

}

void MyLangInterpreter::visit(const MatchExpression &matchExpression) {

}

void MyLangInterpreter::visit(const MatchPair &matchPair) {

}

void MyLangInterpreter::visit(const MatchType &matchType) {

}

void MyLangInterpreter::visit(const MatchNone &matchNone) {

}

void MyLangInterpreter::visit(const Pair &pair) {

}

void MyLangInterpreter::visit(const Typename &type) {

}
