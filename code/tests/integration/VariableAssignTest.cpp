#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"
#include "../../parser/MyLangParser.h"
#include "../../lexer/LexerWithoutComments.h"

TEST(VariableAssignTests, ReassignMutableVariableTest) {
    std::ostringstream oss;
    bool errorOccurred = false;
    bool interpreterErrorOccurred = false;
    auto errorHandler = [&](Position position, ErrorType error) {
        errorOccurred = true;
    };

    auto interpreterErrorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        interpreterErrorOccurred = true;
    };
    const std::string code =
            "mut a = 15;\n"
            "a = 235;\n"
            "standardOutput(a);";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "235\n");
}

TEST(VariableAssignTests, ReassignImmutableVariableTest) {
    std::ostringstream oss;
    bool errorOccurred = false;
    bool interpreterErrorOccurred = false;
    bool exceptionThrown = false;
    auto errorHandler = [&](Position position, ErrorType error) {
        errorOccurred = true;
    };

    auto interpreterErrorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        interpreterErrorOccurred = true;
        ASSERT_EQ(position, Position(1, 2));
        ASSERT_EQ(error, ErrorType::REASSIGN_IMMUTABLE_VARIABLE);
    };
    const std::string code =
            "a = 15;\n"
            "a = 235;\n"
            "standardOutput(a);";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    try {
        interpreter.execute(program);
    } catch (...) {
        exceptionThrown = true;
    }

    ASSERT_FALSE(errorOccurred);
    ASSERT_TRUE(interpreterErrorOccurred);
    ASSERT_TRUE(exceptionThrown);
    ASSERT_EQ(oss.str(), "");
}

TEST(VariableAssignTests, UnknownVariableTest) {
    std::ostringstream oss;
    bool errorOccurred = false;
    bool interpreterErrorOccurred = false;
    bool exceptionThrown = false;
    auto errorHandler = [&](Position position, ErrorType error) {
        errorOccurred = true;
    };

    auto interpreterErrorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        interpreterErrorOccurred = true;
        ASSERT_EQ(position, Position(16, 1));
        ASSERT_EQ(error, ErrorType::UNKNOWN_IDENTIFIER);
    };
    const std::string code =
            "standardOutput(a);";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    try {
        interpreter.execute(program);
    } catch (...) {
        exceptionThrown = true;
    }

    ASSERT_FALSE(errorOccurred);
    ASSERT_TRUE(interpreterErrorOccurred);
    ASSERT_TRUE(exceptionThrown);
    ASSERT_EQ(oss.str(), "");
}