#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteIfStatement, IfPositiveConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "IF condition true"));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> ifInstructions;
    ifInstructions.emplace_back(std::move(print));
    Block::BlockPtr ifBlock = std::make_unique<Block>(std::move(ifInstructions));
    Instruction::InstructionPtr ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(ifBlock),
                                                                            nullptr);
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(ifStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "IF condition true\n");
}

TEST(InterpreteIfStatement, IfNegativeConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "IF condition true"));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> ifInstructions;
    ifInstructions.emplace_back(std::move(print));
    Block::BlockPtr ifBlock = std::make_unique<Block>(std::move(ifInstructions));
    Instruction::InstructionPtr ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(ifBlock),
                                                                            nullptr);
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(ifStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteIfStatement, IfElsePositiveConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printIfArgs;
    printIfArgs.emplace_back(std::make_unique<Constant>(position, "if"));
    Instruction::InstructionPtr printIf = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                         std::move(printIfArgs));

    std::vector<Expression::ExpressionPtr> printElseArgs;
    printElseArgs.emplace_back(std::make_unique<Constant>(position, "else"));
    Instruction::InstructionPtr printElse = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                         std::move(printElseArgs));
    std::vector<Instruction::InstructionPtr> ifInstructions;
    ifInstructions.emplace_back(std::move(printIf));
    Block::BlockPtr ifBlock = std::make_unique<Block>(std::move(ifInstructions));

    std::vector<Instruction::InstructionPtr> elseInstructions;
    elseInstructions.emplace_back(std::move(printElse));
    Block::BlockPtr elseBlock = std::make_unique<Block>(std::move(elseInstructions));


    Instruction::InstructionPtr ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(ifBlock),
                                                                            std::move(elseBlock));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(ifStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "if\n");
}

TEST(InterpreteIfStatement, IfElseNegativeConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printIfArgs;
    printIfArgs.emplace_back(std::make_unique<Constant>(position, "if"));
    Instruction::InstructionPtr printIf = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                         std::move(printIfArgs));

    std::vector<Expression::ExpressionPtr> printElseArgs;
    printElseArgs.emplace_back(std::make_unique<Constant>(position, "else"));
    Instruction::InstructionPtr printElse = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                           std::move(printElseArgs));
    std::vector<Instruction::InstructionPtr> ifInstructions;
    ifInstructions.emplace_back(std::move(printIf));
    Block::BlockPtr ifBlock = std::make_unique<Block>(std::move(ifInstructions));

    std::vector<Instruction::InstructionPtr> elseInstructions;
    elseInstructions.emplace_back(std::move(printElse));
    Block::BlockPtr elseBlock = std::make_unique<Block>(std::move(elseInstructions));


    Instruction::InstructionPtr ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(ifBlock),
                                                                            std::move(elseBlock));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(ifStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "else\n");
}

TEST(InterpreteIfStatement, IfVariablePositiveConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Identifier>(position, "condition");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "IF condition true"));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> ifInstructions;
    ifInstructions.emplace_back(std::move(print));
    Block::BlockPtr ifBlock = std::make_unique<Block>(std::move(ifInstructions));
    Instruction::InstructionPtr ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(ifBlock),
                                                                            nullptr);
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::make_unique<Assign>(std::make_unique<Identifier>(position, "condition"),
                                           std::make_unique<Constant>(position, 1)));
    programInstructions.emplace_back(std::move(ifStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "IF condition true\n");
}

TEST(InterpreteIfStatement, IfVariableNegativeConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Identifier>(position, "condition");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "IF condition true"));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> ifInstructions;
    ifInstructions.emplace_back(std::move(print));
    Block::BlockPtr ifBlock = std::make_unique<Block>(std::move(ifInstructions));
    Instruction::InstructionPtr ifStatement = std::make_unique<IfStatement>(std::move(condition), std::move(ifBlock),
                                                                            nullptr);
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::make_unique<Assign>(std::make_unique<Identifier>(position, "condition"),
                                                              std::make_unique<Constant>(position, 0)));
    programInstructions.emplace_back(std::move(ifStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}
