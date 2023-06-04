#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteCastExpressions, CastIntToFloatTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::FLOAT);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastIntToFloatTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 11);
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::FLOAT);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastIntToIntTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 234);
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::INTEGER);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 234);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastFloatToIntTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 112.139);
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::INTEGER);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 112);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastFloatToIntTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 112.6);
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::INTEGER);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 113);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastStringToIntTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "58");
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::INTEGER);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 58);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastStringToIntFailTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(23, 34);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::INVALID_CONVERSION);
        ASSERT_EQ(position, badPosition);
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(badPosition, "a58");
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::INTEGER);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 58);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastIntToStringTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 18);
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::STRING);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, "18");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastStringToFloatTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "58");
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::FLOAT);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 58.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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

TEST(InterpreteCastExpressions, CastStringToFloatTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, "58.0");
    Expression::ExpressionPtr castExpression = std::make_unique<CastExpression>(position, std::move(constant1),
                                                                                ConstantType::FLOAT);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 58.0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<RelativeExpression>(position, std::move(castExpression), std::move(constant2),
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
