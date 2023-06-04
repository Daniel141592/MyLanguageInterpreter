#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"


TEST(InterpreteAssign, AssingConstantToVariable) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Assign assign(std::make_unique<Identifier>(position, "test"), std::make_unique<Constant>(position, 28));

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.visit(assign);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(InterpreteAssign, AssingConstantToVariableAndPrint) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    std::vector<Instruction::InstructionPtr> instructions;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    instructions.emplace_back(std::make_unique<Assign>(std::make_unique<Identifier>(position, "test"),
                                                       std::make_unique<Constant>(position, 28)));
    std::vector<Expression::ExpressionPtr> args;
    args.emplace_back(std::make_unique<Identifier>(position, "test"));
    instructions.emplace_back(std::make_unique<FunctionCall>(Identifier(position, "standardOutput"), std::move(args)));
    Program program(std::move(instructions));

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "28\n");
}

TEST(InterpreteAssign, AssingUnknownIdentifierToVariable) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(1, 2);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    const std::string unknownIdentifier = "unknown";
    Assign assign(std::make_unique<Identifier>(position, "test"), std::make_unique<Identifier>(badPosition, unknownIdentifier));

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    try {
        interpreter.visit(assign);
    } catch (const UnknownIdentifierException& e) {
        ASSERT_EQ(e.getIdentifier(), unknownIdentifier);
        exceptionThrown = true;
    }
    ASSERT_FALSE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}

TEST(InterpreteAssign, ExecuteAssingUnknownIdentifierToVariable) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    bool exceptionThrown = false;
    Position position(-1, -1);  // dla testu nie ma znaczenia
    Position badPosition(1, 2);
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
        ASSERT_EQ(position, badPosition);
    };
    const std::string unknownIdentifier = "unknown";
    std::vector<Instruction::InstructionPtr> instructions;
    instructions.emplace_back(std::make_unique<Assign>(std::make_unique<Identifier>(position, "test"),
                                                       std::make_unique<Identifier>(badPosition, unknownIdentifier)));
    Program program(std::move(instructions));

    MyLangInterpreter interpreter(oss, iss, errorHandler);

    try {
        interpreter.execute(program);
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
    ASSERT_TRUE(errorOccurred);
}
