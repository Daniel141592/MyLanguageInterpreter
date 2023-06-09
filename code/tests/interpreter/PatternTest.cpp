#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"

TEST(InterpretePatternStatement, EmptyPatternTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 1);
    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpretePatternStatement, PatternWithMatchTypenameTest) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 1);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "Int matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgs)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::INTEGER);
    matches.emplace_back(std::move(matchInt));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "Int matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchTypenameTest2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, "str");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "Int matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgs)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::INTEGER);
    matches.emplace_back(std::move(matchInt));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpretePatternStatement, PatternWithMatchTypenameTest3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, "str");
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "String matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgs)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::STRING);
    matches.emplace_back(std::move(matchInt));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "String matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchTypenameTest4) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 15.8);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "Float matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgs)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::FLOAT);
    matches.emplace_back(std::move(matchInt));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "Float matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchTypenameTest5) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 15);


    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;

    std::vector<Expression::ExpressionPtr> printArgsString;
    printArgsString.emplace_back(std::make_unique<Constant>(position, "String matched"));
    std::vector<Instruction::InstructionPtr> matchStringInstructions;
    matchStringInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgsString)));
    Block::BlockPtr matchStringBlock = std::make_unique<Block>(std::move(matchStringInstructions));
    MatchStatement::MatchStatementPtr matchString = std::make_unique<MatchType>(std::move(matchStringBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::STRING);
    matches.emplace_back(std::move(matchString));

    std::vector<Expression::ExpressionPtr> printArgsInt;
    printArgsInt.emplace_back(std::make_unique<Constant>(position, "Int matched"));
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgsInt)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::INTEGER);
    matches.emplace_back(std::move(matchInt));

    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "Int matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchTypenameTest6) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 1.5);


    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;

    std::vector<Expression::ExpressionPtr> printArgsString;
    printArgsString.emplace_back(std::make_unique<Constant>(position, "String matched"));
    std::vector<Instruction::InstructionPtr> matchStringInstructions;
    matchStringInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                        std::move(printArgsString)));
    Block::BlockPtr matchStringBlock = std::make_unique<Block>(std::move(matchStringInstructions));
    MatchStatement::MatchStatementPtr matchString = std::make_unique<MatchType>(std::move(matchStringBlock),
                                                                                std::make_unique<Identifier>(position,
                                                                                                             "x"),
                                                                                ConstantType::STRING);
    matches.emplace_back(std::move(matchString));

    std::vector<Expression::ExpressionPtr> printArgsInt;
    printArgsInt.emplace_back(std::make_unique<Constant>(position, "Int matched"));
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgsInt)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::INTEGER);
    matches.emplace_back(std::move(matchInt));

    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpretePatternStatement, PatternMatchNone) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 1.5);


    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;

    std::vector<Expression::ExpressionPtr> printArgsString;
    printArgsString.emplace_back(std::make_unique<Constant>(position, "String matched"));
    std::vector<Instruction::InstructionPtr> matchStringInstructions;
    matchStringInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                        std::move(printArgsString)));
    Block::BlockPtr matchStringBlock = std::make_unique<Block>(std::move(matchStringInstructions));
    MatchStatement::MatchStatementPtr matchString = std::make_unique<MatchType>(std::move(matchStringBlock),
                                                                                std::make_unique<Identifier>(position,
                                                                                                             "x"),
                                                                                ConstantType::STRING);
    matches.emplace_back(std::move(matchString));

    std::vector<Expression::ExpressionPtr> printArgsInt;
    printArgsInt.emplace_back(std::make_unique<Constant>(position, "Int matched"));
    std::vector<Instruction::InstructionPtr> matchIntInstructions;
    matchIntInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgsInt)));
    Block::BlockPtr matchIntBlock = std::make_unique<Block>(std::move(matchIntInstructions));
    MatchStatement::MatchStatementPtr matchInt = std::make_unique<MatchType>(std::move(matchIntBlock),
                                                                             std::make_unique<Identifier>(position,
                                                                                                          "x"),
                                                                             ConstantType::INTEGER);
    matches.emplace_back(std::move(matchInt));

    std::vector<Expression::ExpressionPtr> printArgsNone;
    printArgsNone.emplace_back(std::make_unique<Constant>(position, "none matched"));
    std::vector<Instruction::InstructionPtr> matchNoneInstructions;
    matchNoneInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                     std::move(printArgsNone)));
    Block::BlockPtr matchNoneBlock = std::make_unique<Block>(std::move(matchNoneInstructions));
    MatchStatement::MatchStatementPtr matchNone = std::make_unique<MatchNone>(std::move(matchNoneBlock));
    matches.emplace_back(std::move(matchNone));

    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "none matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchExpressionTest4) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr condition = std::make_unique<Constant>(position, 15.8);
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "expression matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchExpressionInstructions;
    matchExpressionInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                            std::move(printArgs)));
    Block::BlockPtr matchExpressionBlock = std::make_unique<Block>(std::move(matchExpressionInstructions));
    Expression::ExpressionPtr expression = std::make_unique<Constant>(position, 15.8);
    MatchStatement::MatchStatementPtr matchExpression = std::make_unique<MatchExpression>(std::move(expression),
                                                                                          std::make_unique<Identifier>(
                                                                                                  position, "x"),
                                                                                          std::move(
                                                                                                  matchExpressionBlock));
    matches.emplace_back(std::move(matchExpression));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "expression matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchPair) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr first = std::make_unique<Constant>(position, 165);
    Expression::ExpressionPtr second = std::make_unique<Constant>(position, 18);
    Expression::ExpressionPtr condition = std::make_unique<Pair>(std::move(first), std::move(second));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "pair matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchPairInstructions;
    matchPairInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                      std::move(printArgs)));
    Block::BlockPtr matchPairBlock = std::make_unique<Block>(std::move(matchPairInstructions));

    MatchStatement::MatchStatementPtr matchPair = std::make_unique<MatchPair>(std::move(matchPairBlock),
                                                                              std::make_unique<Identifier>(position,
                                                                                                           "x"),
                                                                              std::make_unique<Identifier>(position,
                                                                                                           "y"));
    matches.emplace_back(std::move(matchPair));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "pair matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchPair2) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr first = std::make_unique<Constant>(position, 165);
    Expression::ExpressionPtr second = std::make_unique<Constant>(position, 18);
    Expression::ExpressionPtr condition = std::make_unique<Pair>(std::move(first), std::move(second));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "pair matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchPairInstructions;
    matchPairInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                      std::move(printArgs)));
    Block::BlockPtr matchPairBlock = std::make_unique<Block>(std::move(matchPairInstructions));

    MatchStatement::MatchStatementPtr matchPair = std::make_unique<MatchPair>(std::move(matchPairBlock),
                                                                              std::make_unique<Constant>(position,
                                                                                                           165),
                                                                              std::make_unique<Identifier>(position,
                                                                                                           "y"));
    matches.emplace_back(std::move(matchPair));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "pair matched\n");
}

TEST(InterpretePatternStatement, PatternWithMatchPair3) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Expression::ExpressionPtr first = std::make_unique<Constant>(position, 16);
    Expression::ExpressionPtr second = std::make_unique<Constant>(position, 18);
    Expression::ExpressionPtr condition = std::make_unique<Pair>(std::move(first), std::move(second));
    std::vector<Expression::ExpressionPtr> printArgs;
    printArgs.emplace_back(std::make_unique<Constant>(position, "pair matched"));

    std::vector<Instruction::InstructionPtr> programInstructions;
    std::vector<MatchStatement::MatchStatementPtr> matches;
    std::vector<Instruction::InstructionPtr> matchPairInstructions;
    matchPairInstructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"),
                                                                      std::move(printArgs)));
    Block::BlockPtr matchPairBlock = std::make_unique<Block>(std::move(matchPairInstructions));

    MatchStatement::MatchStatementPtr matchPair = std::make_unique<MatchPair>(std::move(matchPairBlock),
                                                                              std::make_unique<Constant>(position,
                                                                                                         165),
                                                                              std::make_unique<Identifier>(position,
                                                                                                           "y"));
    matches.emplace_back(std::move(matchPair));
    Instruction::InstructionPtr patternStatement = std::make_unique<PatternStatement>(std::move(condition),
                                                                                      std::move(matches));
    programInstructions.emplace_back(std::move(patternStatement));
    Program program(std::move(programInstructions));
    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}
