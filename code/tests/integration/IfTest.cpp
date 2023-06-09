#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"
#include "../../parser/MyLangParser.h"
#include "../../lexer/LexerWithoutComments.h"

TEST(IfTests, BasicIfTest) {
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
            "zmienna = 20;\n"
            "if zmienna > 19 {\n"
            "    standardOutput(\"IF\");\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "IF\n");
}

TEST(IfTests, IfWithoutParenthesis) {
    std::ostringstream oss;
    bool errorOccurred = false;
    bool interpreterErrorOccurred = false;
    bool exceptionThrown = false;
    auto errorHandler = [&](Position position, ErrorType error) {
        errorOccurred = true;
        ASSERT_EQ(error, ErrorType::BLOCK_EXPECTED);
        ASSERT_EQ(position, Position(5, 3));
    };

    auto interpreterErrorHandler = [&](Position position, ErrorType error, const std::string& msg) {
        interpreterErrorOccurred = true;
    };
    const std::string code =
            "zmienna = 20;\n"
            "if zmienna > 19\n"
            "    standardOutput(\"IF\");\n"
            "}";
    std::istringstream iss(code);
    try {
        LexerWithoutComments lexerWithoutComments(iss, errorHandler);
        MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
        Program program = parser.parse();
        MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
        interpreter.execute(program);
    } catch (...) {
        exceptionThrown = true;
    }

    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "");
}

TEST(IfTests, BasicIfElseTest) {
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
            "zmienna = 20;\n"
            "if zmienna > 19 {\n"
            "    standardOutput(\"IF\");\n"
            "} else {\n"
            "    standardOutput(\"ELSE\");\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "IF\n");
}

TEST(IfTests, BasicIfElseTest2) {
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
            "zmienna = 2;\n"
            "if zmienna > 19 {\n"
            "    standardOutput(\"IF\");\n"
            "} else {\n"
            "    standardOutput(\"ELSE\");\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "ELSE\n");
}

TEST(IfTests, IfVariableShadowingTest) {
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
            "zmienna = 20;\n"
            "inna = 35;\n"
            "standardOutput(\"inna: \"+String(inna));\n"
            "if zmienna > 19 {\n"
            "    mut inna = 15;\n"
            "    standardOutput(\"inna: \"+String(inna));\n"
            "}\n"
            "standardOutput(\"inna: \"+String(inna));";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "inna: 35\ninna: 15\ninna: 35\n");
}
