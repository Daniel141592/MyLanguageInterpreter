#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteBooleanExpressions, OrTest) {
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
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, OrTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, OrTest3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, OrTest4) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, OrTest5) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 100);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, -5);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, AndTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, AndTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, AndTest3) {
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
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, AndTest4) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, AndTest5) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1001);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, -231);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(constant1), std::move(constant2)));
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

TEST(InterpreteBooleanExpressions, ComplexLogicalTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr andExpression = std::make_unique<AndExpression>(position, std::move(constant1),
                                                                              std::move(constant2));
    Expression::ExpressionPtr constant3 = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(andExpression), std::move(constant3)));
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

TEST(InterpreteBooleanExpressions, ComplexLogicalTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr andExpression = std::make_unique<AndExpression>(position, std::move(constant1),
                                                                              std::move(constant2));
    Expression::ExpressionPtr constant3 = std::make_unique<Constant>(position, 213);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(andExpression), std::move(constant3)));
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

TEST(InterpreteBooleanExpressions, ComplexLogicalTest3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr andExpression = std::make_unique<AndExpression>(position, std::move(constant1),
                                                                              std::move(constant2));
    Expression::ExpressionPtr constant3 = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(andExpression), std::move(constant3)));
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

TEST(InterpreteBooleanExpressions, ComplexLogicalTest4) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr andExpression1 = std::make_unique<AndExpression>(position, std::move(constant1),
                                                                              std::move(constant2));
    Expression::ExpressionPtr constant3 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr constant4 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr andExpression2 = std::make_unique<AndExpression>(position, std::move(constant3),
                                                                              std::move(constant4));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<OrExpression>(position, std::move(andExpression1), std::move(andExpression2)));
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

TEST(InterpreteBooleanExpressions, ComplexLogicalTest5) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr constant1 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr constant2 = std::make_unique<Constant>(position, 1);
    Expression::ExpressionPtr andExpression1 = std::make_unique<OrExpression>(position, std::move(constant1),
                                                                               std::move(constant2));
    Expression::ExpressionPtr constant3 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr constant4 = std::make_unique<Constant>(position, 0);
    Expression::ExpressionPtr andExpression2 = std::make_unique<OrExpression>(position, std::move(constant3),
                                                                               std::move(constant4));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<AndExpression>(position, std::move(andExpression1), std::move(andExpression2)));
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
