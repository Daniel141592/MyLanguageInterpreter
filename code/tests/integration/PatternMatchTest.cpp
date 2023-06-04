#include <gtest/gtest.h>
#include "../../structure/Program.h"
#include "../../interpreter/MyLangInterpreter.h"
#include "../../parser/MyLangParser.h"
#include "../../lexer/LexerWithoutComments.h"

TEST(IntegrationPatternMatchTests, PatternMatchPairTest) {
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
            "mut para = 15, 17;\n"
            "pattern para {\n"
            "    match Int (x) {\n"
            "        standardOutput(\"zmienna jest intem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match String (x) {\n"
            "        standardOutput(\"zmienna jest stringiem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match 15, x {\n"
            "        standardOutput(\"zmienna jest parą, której pierwsza składowa wynosi 15, a druga: \"+String(x));\n"
            "    }\n"
            "    match none {\n"
            "        standardOutput(\"zmienna jest czymś innym\");\n"
            "    }\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "zmienna jest parą, której pierwsza składowa wynosi 15, a druga: 17\n");
}

TEST(IntegrationPatternMatchTests, PatternMatchExpressionFunctionTest) {
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
            "func even(x) {\n"
            "    return x % 2 == 0;\n"
            "}\n"
            "mut var = 16;\n"
            "pattern var {\n"
            "    match (even) (x) {\n"
            "        standardOutput(\"zmienna jest parzysta, x = \"+String(x));\n"
            "    }\n"
            "    match Int (x) {\n"
            "        standardOutput(\"zmienna jest intem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match String (x) {\n"
            "        standardOutput(\"zmienna jest stringiem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match 15, x {\n"
            "        standardOutput(\"zmienna jest parą, której pierwsza składowa wynosi 15, a druga: \"+String(x));\n"
            "    }\n"
            "    match none {\n"
            "        standardOutput(\"zmienna jest czymś innym\");\n"
            "    }\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "zmienna jest parzysta, x = 16\n");
}

TEST(IntegrationPatternMatchTests, PatternMatchFirstMatchingBlock) {
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
            "func even(x) {\n"
            "    return x % 2 == 0;\n"
            "}\n"
            "mut var = 216;\n"
            "pattern var {\n"
            "    match Int (x) {\n"
            "        standardOutput(\"zmienna jest intem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match (even) (x) {\n"
            "        standardOutput(\"zmienna jest parzysta, x = \"+String(x));\n"
            "    }\n"
            "    match String (x) {\n"
            "        standardOutput(\"zmienna jest stringiem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match 15, x {\n"
            "        standardOutput(\"zmienna jest parą, której pierwsza składowa wynosi 15, a druga: \"+String(x));\n"
            "    }\n"
            "    match none {\n"
            "        standardOutput(\"zmienna jest czymś innym\");\n"
            "    }\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "zmienna jest intem i wynosi: 216\n");
}

TEST(IntegrationPatternMatchTests, PatternMatchArithmeticExpression) {
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
            "func even(x) {\n"
            "    return x % 2 == 0;\n"
            "}\n"
            "mut var = 216;\n"
            "pattern var {\n"
            "    match 4 * 50 + 4 * 4 (x) {\n"
            "        standardOutput(\"4 * 50 + 4 * 4 = \"+String(x));\n"
            "    }\n"
            "    match 15, x {\n"
            "        standardOutput(\"zmienna jest parą, której pierwsza składowa wynosi 15, a druga: \"+String(x));\n"
            "    }\n"
            "    match none {\n"
            "        standardOutput(\"zmienna jest czymś innym\");\n"
            "    }\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "4 * 50 + 4 * 4 = 216\n");
}

TEST(IntegrationPatternMatchTests, PatternMatchNone) {
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
            "func even(x) {\n"
            "    return x % 2 == 0;\n"
            "}\n"
            "mut var = 16, 17;\n"
            "pattern var {\n"
            "    match Int (x) {\n"
            "        standardOutput(\"zmienna jest intem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match String (x) {\n"
            "        standardOutput(\"zmienna jest stringiem i wynosi: \"+String(x));\n"
            "    }\n"
            "    match 15, x {\n"
            "        standardOutput(\"zmienna jest parą, której pierwsza składowa wynosi 15, a druga: \"+String(x));\n"
            "    }\n"
            "    match none {\n"
            "        standardOutput(\"match none\");\n"
            "    }\n"
            "}";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "match none\n");
}
