#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"


TEST(InterpreteVariableDeclaration, VariableDeclarationWithoutValue) {
    std::ostringstream oss;
    std::istringstream iss;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    bool errorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    VariableDeclaration declaration(std::make_unique<Identifier>(position, "test"));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.visit(declaration);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteVariableDeclaration, VariableDeclarationWithValue) {
    std::ostringstream oss;
    std::istringstream iss;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    bool errorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr expression = std::make_unique<Constant>(position, 20);
    VariableDeclaration declaration(std::make_unique<Identifier>(position, "test"), std::move(expression));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.visit(declaration);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteVariableDeclaration, VariableDeclarationAndThenReasign) {
    std::ostringstream oss;
    std::istringstream iss;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    bool errorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    const std::string variableName = "test";
    Expression::ExpressionPtr expression = std::make_unique<Constant>(position, 20);
    Expression::ExpressionPtr expression2 = std::make_unique<Constant>(position, 320);
    Instruction::InstructionPtr declaration = std::make_unique<VariableDeclaration>(
            std::make_unique<Identifier>(position, variableName), std::move(expression));
    Instruction::InstructionPtr reassign = std::make_unique<Assign>(
            std::make_unique<Identifier>(position, variableName), std::move(expression2));

    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(declaration));
    programInstructions.emplace_back(std::move(reassign));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Identifier>(position, variableName));
    programInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                    std::move(printArgs)));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "320\n");
}

TEST(InterpreteVariableDeclaration, ImmutableVariableReassign) {
    std::ostringstream oss;
    std::istringstream iss;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(3, 8);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(position, badPosition);
        ASSERT_EQ(error, ErrorType::REASSIGN_IMMUTABLE_VARIABLE);
    };
    const std::string variableName = "test";
    Expression::ExpressionPtr expression = std::make_unique<Constant>(position, 20);
    Expression::ExpressionPtr expression2 = std::make_unique<Constant>(position, 320);
    Instruction::InstructionPtr declaration = std::make_unique<Assign>(
            std::make_unique<Identifier>(position, variableName), std::move(expression));
    Instruction::InstructionPtr reassign = std::make_unique<Assign>(
            std::make_unique<Identifier>(badPosition, variableName), std::move(expression2));

    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(declaration));
    programInstructions.emplace_back(std::move(reassign));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Identifier>(position, variableName));
    programInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                    std::move(printArgs)));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    try {
        interpreter.execute(program);
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
    ASSERT_EQ(oss.str(), "");
}
