#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteArithmeticExpressions, AdditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AdditiveExpression>(position, std::move(constant1), std::move(constant2),
                                                                AdditiveType::ADD));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "5\n");
}

TEST(InterpreteArithmeticExpressions, SubtractTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AdditiveExpression>(position, std::move(constant1), std::move(constant2),
                                                                AdditiveType::SUBTRACT));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "1\n");
}

TEST(InterpreteArithmeticExpressions, MultiplicationTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                MultiplicativeType::MULTIPLY));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "6\n");
}

TEST(InterpreteArithmeticExpressions, DivisionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                      MultiplicativeType::DIVIDE));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "1\n");
}

TEST(InterpreteArithmeticExpressions, DivisionByZeroTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(1, 2);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(position, badPosition);
        ASSERT_EQ(error, ErrorType::DIVISION_BY_ZERO);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(badPosition, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                      MultiplicativeType::DIVIDE));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

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

TEST(InterpreteArithmeticExpressions, ModuloTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 19);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 4);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                      MultiplicativeType::MODULO));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "3\n");
}

TEST(InterpreteArithmeticExpressions, ModuloTestWithFloat) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(2, 3);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::INVALID_OPERAND);
        ASSERT_EQ(position, badPosition);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 19.0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(badPosition, 4.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                      MultiplicativeType::MODULO));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

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

TEST(InterpreteArithmeticExpressions, DivisionWithFloatNumbersTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3.0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                      MultiplicativeType::DIVIDE));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "1.5\n");
}

TEST(InterpreteArithmeticExpressions, IntDivisionWithFloatNumbersTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 3.0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<MultiplicationExpression>(position, std::move(constant1), std::move(constant2),
                                                                      MultiplicativeType::INT_DIVIDE));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "1\n");
}
