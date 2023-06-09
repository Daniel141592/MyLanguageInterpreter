#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpreteLoopStatement, LoopNegativeConditionTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 0);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "message from loop"));
    Instruction::InstructionPtr print = std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                       std::move(printArgs));
    std::vector<Instruction::InstructionPtr> loopInstructions;
    loopInstructions.emplace_back(std::move(print));
    Block::BlockPtr loopBlock = std::make_unique<Block>(std::move(loopInstructions));
    Instruction::InstructionPtr loopStatement = std::make_unique<LoopStatement>(std::move(condition), std::move(loopBlock));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(loopStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteLoopStatement, LoopChangeConditionToNegativeAfterOneIterationTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    const std::string conditionVariableName = "condition";
    Identifier::IdentifierPtr conditionVariableId = std::make_unique<Identifier>(position, conditionVariableName);
    Expression::ExpressionPtr conditionInitialValue = std::make_unique<Constant>(position, 1);
    Instruction::InstructionPtr variable = std::make_unique<VariableDeclaration>(std::move(conditionVariableId),
                                                                                 std::move(conditionInitialValue),
                                                                                 true);
    Expression::ExpressionPtr condition = std::make_unique<Identifier>(position, conditionVariableName);

    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "message from loop"));
    std::vector<Instruction::InstructionPtr> loopInstructions;
    loopInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                           std::move(printArgs)));
    loopInstructions.emplace_back(
            std::make_unique<Assign>(std::make_unique<Identifier>(position, conditionVariableName),
                                     std::make_unique<Constant>(position, 0)));
    Block::BlockPtr loopBlock = std::make_unique<Block>(std::move(loopInstructions));
    Instruction::InstructionPtr loopStatement = std::make_unique<LoopStatement>(std::move(condition), std::move(loopBlock));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(variable));
    programInstructions.emplace_back(std::move(loopStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "message from loop\n");
}

TEST(InterpreteLoopStatement, LoopTwoIterationsTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    const std::string conditionVariableName = "condition";
    Identifier::IdentifierPtr conditionVariableId = std::make_unique<Identifier>(position, conditionVariableName);
    Expression::ExpressionPtr conditionInitialValue = std::make_unique<Constant>(position, 2);
    Instruction::InstructionPtr variable = std::make_unique<VariableDeclaration>(std::move(conditionVariableId),
                                                                                 std::move(conditionInitialValue),
                                                                                 true);
    Expression::ExpressionPtr condition = std::make_unique<Identifier>(position, conditionVariableName);

    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "message from loop"));
    std::vector<Instruction::InstructionPtr> loopInstructions;
    loopInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                 std::move(printArgs)));
    loopInstructions.emplace_back(
            std::make_unique<Assign>(std::make_unique<Identifier>(position, conditionVariableName),
                                     std::make_unique<AdditiveExpression>(position,
                                                                          std::make_unique<Identifier>(position,
                                                                                                       conditionVariableName),
                                                                          std::make_unique<Constant>(position, 1),
                                                                          AdditiveType::SUBTRACT)));
    Block::BlockPtr loopBlock = std::make_unique<Block>(std::move(loopInstructions));
    Instruction::InstructionPtr loopStatement = std::make_unique<LoopStatement>(std::move(condition), std::move(loopBlock));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(variable));
    programInstructions.emplace_back(std::move(loopStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "message from loop\nmessage from loop\n");
}

TEST(InterpreteLoopStatement, LoopThreeIterationsTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    const std::string conditionVariableName = "condition";
    Identifier::IdentifierPtr conditionVariableId = std::make_unique<Identifier>(position, conditionVariableName);
    Expression::ExpressionPtr conditionInitialValue = std::make_unique<Constant>(position, 3);
    Instruction::InstructionPtr variable = std::make_unique<VariableDeclaration>(std::move(conditionVariableId),
                                                                                 std::move(conditionInitialValue),
                                                                                 true);
    Expression::ExpressionPtr condition = std::make_unique<Identifier>(position, conditionVariableName);

    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "loop"));
    std::vector<Instruction::InstructionPtr> loopInstructions;
    loopInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                 std::move(printArgs)));
    loopInstructions.emplace_back(
            std::make_unique<Assign>(std::make_unique<Identifier>(position, conditionVariableName),
                                     std::make_unique<AdditiveExpression>(position,
                                                                          std::make_unique<Identifier>(position,
                                                                                                       conditionVariableName),
                                                                          std::make_unique<Constant>(position, 1),
                                                                          AdditiveType::SUBTRACT)));
    Block::BlockPtr loopBlock = std::make_unique<Block>(std::move(loopInstructions));
    Instruction::InstructionPtr loopStatement = std::make_unique<LoopStatement>(std::move(condition), std::move(loopBlock));
    std::vector<Instruction::InstructionPtr> programInstructions;
    programInstructions.emplace_back(std::move(variable));
    programInstructions.emplace_back(std::move(loopStatement));

    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "loop\nloop\nloop\n");
}

