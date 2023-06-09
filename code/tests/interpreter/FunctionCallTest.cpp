#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteFunctionCall, BasicFunctionCall) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    std::vector<Instruction::InstructionPtr> functionInstructions;
    std::vector<Expression::ExpressionPtr> printArgs;
    const std::string expectedOutput = "should print";
    printArgs.emplace_back(std::make_unique<Constant>(position, expectedOutput));
    functionInstructions.emplace_back(
            std::make_unique<FunctionCall>(Identifier(position, "standardOutput"), std::move(printArgs)));

    Block::BlockPtr block = std::make_unique<Block>(std::move(functionInstructions));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(
            std::make_unique<FunctionDeclaration>(position, "functionName", std::move(block), std::vector<Argument>()));
    programInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "functionName"),
                                                                    std::vector<Expression::ExpressionPtr>()));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "should print\n");
}

TEST(InterpreteFunctionCall, UndefinedFunctionCall) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position badPosition(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(position, badPosition);
        ASSERT_EQ(error, ErrorType::UNKNOWN_IDENTIFIER);
    };
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(badPosition, "functionName"),
                                                                    std::vector<Expression::ExpressionPtr>()));
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

TEST(InterpreteFunctionCall, IdentifiersDeclaredInOtherFunctionAreNotVisibleInFunctionBody) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(1, 1);  // dla testu nie ma znaczenia
    Position badPosition(-1, -1);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(position, badPosition);
        ASSERT_EQ(error, ErrorType::UNKNOWN_IDENTIFIER);
    };

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<Instruction::InstructionPtr> firstFunctionInstructions;
    firstFunctionInstructions.emplace_back(std::make_unique<Assign>(std::make_unique<Identifier>(position, "inFunction"),
                                                                    std::make_unique<Identifier>(badPosition, "test")));
    Block::BlockPtr firstFunctionBlock = std::make_unique<Block>(std::move(firstFunctionInstructions));
    programInstructions.emplace_back(
            std::make_unique<FunctionDeclaration>(position, "firstFunctionName", std::move(firstFunctionBlock),
                                                  std::vector<Argument>()));
    std::vector<Instruction::InstructionPtr> secondFunctionInstructions;
    secondFunctionInstructions.emplace_back(std::make_unique<Assign>(std::make_unique<Identifier>(position, "test"),
                                                                    std::make_unique<Constant>(position, 28)));
    secondFunctionInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(badPosition, "firstFunctionName"),
                                                                           std::vector<Expression::ExpressionPtr>()));
    Block::BlockPtr secondFunctionBlock = std::make_unique<Block>(std::move(secondFunctionInstructions));
    programInstructions.emplace_back(
            std::make_unique<FunctionDeclaration>(position, "secondFunctionDeclaration", std::move(secondFunctionBlock),
                                                  std::vector<Argument>()));
    programInstructions.emplace_back(
            std::make_unique<FunctionCall>(Identifier(position, "secondFunctionDeclaration"),
                                           std::vector<Expression::ExpressionPtr>()));
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
