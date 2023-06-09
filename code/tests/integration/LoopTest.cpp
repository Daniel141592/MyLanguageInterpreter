#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"
#include "../../parser/MyLangParser.h"
#include "../../lexer/LexerWithoutComments.h"

TEST(LoopTests, BasicLoopTest) {
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
            "mut licznik = 1;\n"
            "loop licznik <= 10 {\n"
            "    standardOutput(licznik);\n"
            "    licznik = licznik + 1;\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
}

TEST(LoopTests, LoopWithFalseConditionTest) {
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
            "mut licznik = 1;\n"
            "loop licznik > 10 {\n"
            "    standardOutput(licznik);\n"
            "    licznik = licznik + 1;\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "");
}
