#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteRelativeExpressions, EqualTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::EQUAL));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "0\n");
}

TEST(InterpreteRelativeExpressions, EqualTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 2023);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 2023);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::EQUAL));
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

TEST(InterpreteRelativeExpressions, EqualTest3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "abcd");
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, "abcd");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::EQUAL));
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

TEST(InterpreteRelativeExpressions, EqualTestIncompatibleTypes) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(16, 12);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::INVALID_OPERAND);
        ASSERT_EQ(position, badPosition);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 15);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(badPosition, "abcd");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::EQUAL));
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

TEST(InterpreteRelativeExpressions, NotEqualTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "abcd");
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, "abcde");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::NOT_EQUAL));
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

TEST(InterpreteRelativeExpressions, NotEqualTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.17);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.17);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::NOT_EQUAL));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "0\n");
}

TEST(InterpreteRelativeExpressions, NotEqualTestIncompatibleTypes) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(16, 12);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::INVALID_OPERAND);
        ASSERT_EQ(position, badPosition);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 15);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(badPosition, "abcd");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::NOT_EQUAL));
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

TEST(InterpreteRelativeExpressions, GreaterThanTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.17);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.15);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::GREATER));
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

TEST(InterpreteRelativeExpressions, GreaterThanTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 7.17);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.15);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::GREATER));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "0\n");
}

TEST(InterpreteRelativeExpressions, GreaterThanTestIncompatibleTypes) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(16, 12);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::INVALID_OPERAND);
        ASSERT_EQ(position, badPosition);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 15);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(badPosition, "abcd");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::GREATER));
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

TEST(InterpreteRelativeExpressions, LessThanTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.17);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.15);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::LESS));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "0\n");
}

TEST(InterpreteRelativeExpressions, LessThanTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.15);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::LESS));
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

TEST(InterpreteRelativeExpressions, LessThannTestIncompatibleTypes) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(16, 12);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::INVALID_OPERAND);
        ASSERT_EQ(position, badPosition);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 15);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(badPosition, "abcd");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::LESS));
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

TEST(InterpreteRelativeExpressions, LessEqualThanTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.15);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::LESS_EQUAL));
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

TEST(InterpreteRelativeExpressions, LessEqualThanTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 5);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 5);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::LESS_EQUAL));
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

TEST(InterpreteRelativeExpressions, LessEqualThanTest3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 54);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 5);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::LESS_EQUAL));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "0\n");
}

TEST(InterpreteRelativeExpressions, IsTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 17.1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::IS));
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

TEST(InterpreteRelativeExpressions, IsTestTypename) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.1);
    Expression::ExpressionPtr constant2 = std::make_unique<Typename>(position, ConstantType::FLOAT);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::IS));
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

TEST(InterpreteRelativeExpressions, IsTestTypename2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 17.1);
    Expression::ExpressionPtr constant2 = std::make_unique<Typename>(position, ConstantType::STRING);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::IS));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(print));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "0\n");
}

TEST(InterpreteRelativeExpressions, IsTestTypename3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1024);
    Expression::ExpressionPtr constant2 = std::make_unique<Typename>(position, ConstantType::INTEGER);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::IS));
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

TEST(InterpreteRelativeExpressions, IsTestTypename4) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "text");
    Expression::ExpressionPtr constant2 = std::make_unique<Typename>(position, ConstantType::STRING);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::IS));
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

TEST(InterpreteRelativeExpressions, IsTestTypename5) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "1234");
    Expression::ExpressionPtr constant2 = std::make_unique<Typename>(position, ConstantType::STRING);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(constant1), std::move(constant2),
                                                                RelativeType::IS));
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

