#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"


TEST(InterpretetProgram, InterpretEmptyProgram) {
    std::ostringstream oss;
    std::istringstream iss;
    bool errorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        errorOccurred = true;
    };
    std::vector<Instruction::InstructionPtr> instructions;
    Program program(std::move(instructions));

    MyLangInterpreter interpreter(oss, iss, errorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_EQ(oss.str(), "");
}