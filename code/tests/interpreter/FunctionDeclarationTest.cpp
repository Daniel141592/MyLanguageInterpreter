#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"


TEST(InterpreteFunctionDeclaration, BasicFunctionDeclaration) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    std::vector<Instruction::InstructionPtr> functionInstructions;
    Block::BlockPtr block = std::make_unique<Block>(std::move(functionInstructions));
    FunctionDeclaration functionDeclaration(position, "functionName", std::move(block));

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.visit(functionDeclaration);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteFunctionDeclaration, BasicFunctionDeclarationWithArguments) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    std::vector<Instruction::InstructionPtr> functionInstructions;
    Block::BlockPtr block = std::make_unique<Block>(std::move(functionInstructions));
    std::vector<Argument> args;
    args.emplace_back(position, "argname");
    FunctionDeclaration functionDeclaration(position, "functionName", std::move(block), args);

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.visit(functionDeclaration);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteFunctionDeclaration, BasicFunctionDeclarationWithoutCalling) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    std::vector<Instruction::InstructionPtr> functionInstructions;
    std::vector<Expression::ExpressionPtr> args;
    args.emplace_back(std::make_unique<Constant>(position, "Should not print!"));
    functionInstructions.emplace_back(
            std::make_unique<FunctionCall>(Identifier(position, "standardOutput"), std::move(args)));

    Block::BlockPtr block = std::make_unique<Block>(std::move(functionInstructions));
    FunctionDeclaration functionDeclaration(position, "functionName", std::move(block));

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.visit(functionDeclaration);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteFunctionDeclaration, BasicFunctionDeclarationWithFunctionCall) {
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

TEST(InterpreteFunctionDeclaration, RedefinitinOfFunctionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(1, 2);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(position, badPosition);
        ASSERT_EQ(error, ErrorType::IDENTIFIER_REDEFINITION);
    };

    Block::BlockPtr block = std::make_unique<Block>(std::vector<Instruction::InstructionPtr>());
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(
            std::make_unique<FunctionDeclaration>(position, "functionName", std::move(block), std::vector<Argument>()));
    programInstructions.emplace_back(
            std::make_unique<FunctionDeclaration>(badPosition, "functionName", std::move(block), std::vector<Argument>()));

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