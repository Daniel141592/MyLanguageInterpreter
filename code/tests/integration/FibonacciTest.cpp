#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"
#include "../../parser/MyLangParser.h"
#include "../../lexer/LexerWithoutComments.h"

TEST(FibonacciTests, FibonacciTest) {
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
            "func fibonacci(num) {\n"
            "    if num <= 0 {\n"
            "        return \"Wprowadź poprawną wartość num > 0\";\n"
            "    }\n"
            "    if num == 1 {\n"
            "        return 0;\n"
            "    }\n"
            "    if num == 2 {\n"
            "        return 1;\n"
            "    }\n"
            "    return fibonacci(num - 1) + fibonacci(num - 2);\n"
            "}\n"
            "standardOutput(fibonacci(5));";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "3\n");
}

TEST(FibonacciTests, FibonacciTest2) {
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
            "func fibonacci(num) {\n"
            "    if num <= 0 {\n"
            "        return \"Wprowadź poprawną wartość num > 0\";\n"
            "    }\n"
            "    if num == 1 {\n"
            "        return 0;\n"
            "    }\n"
            "    if num == 2 {\n"
            "        return 1;\n"
            "    }\n"
            "    return fibonacci(num - 1) + fibonacci(num - 2);\n"
            "}\n"
            "standardOutput(fibonacci(6));";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "5\n");
}

TEST(FibonacciTests, FibonacciTest3) {
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
            "func fibonacci(num) {\n"
            "    if num <= 0 {\n"
            "        return \"Wprowadź poprawną wartość num > 0\";\n"
            "    }\n"
            "    if num == 1 {\n"
            "        return 0;\n"
            "    }\n"
            "    if num == 2 {\n"
            "        return 1;\n"
            "    }\n"
            "    return fibonacci(num - 1) + fibonacci(num - 2);\n"
            "}\n"
            "standardOutput(fibonacci(7));";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "8\n");
}
