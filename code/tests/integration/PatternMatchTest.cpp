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

TEST(IntegrationPatternMatchTests, ComplexPatternMatchTest) {
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
            "    if !(x is Int) {\n"
            "        return 0;\n"
            "    }\n"
            "    return x % 2 == 0;\n"
            "}\n"
            "\n"
            "\n"
            "func describe(zmienna) {\n"
            "    pattern zmienna {\n"
            "        match (32) (x) {\n"
            "            standardOutput(\"match expression: 32, wartość x: \"+String(x));\n"
            "        }\n"
            "        match (3 * 10 + 3) (x) {\n"
            "            standardOutput(\"match expression: 3 * 10 + 3, wartość x: \"+String(x));\n"
            "        }\n"
            "        match (even) (x) {\n"
            "            standardOutput(\"zmienna jest parzysta, x = \"+String(x));\n"
            "        }\n"
            "        match 21, 35 {\n"
            "            standardOutput(\"pierwszy element stały 21, drugi element stały 35\");\n"
            "        }\n"
            "        match x, 35 {\n"
            "            standardOutput(\"pierwszy element: \"+String(x)+\", drugi stały 35\");\n"
            "        }\n"
            "        match x, y {\n"
            "            standardOutput(\"pierwszy element: \"+String(x)+\", drugi element: \"+String(35));\n"
            "        }\n"
            "        match x, 3 {\n"
            "            standardOutput(\"pierwszy element: \"+String(x)+\", drugi stały 3\");\n"
            "        }\n"
            "        match Int (x) {\n"
            "            standardOutput(\"zmienna jest intem i wynosi: \"+String(x));\n"
            "        }\n"
            "        match String (x) {\n"
            "            standardOutput(\"zmienna jest stringiem i wynosi: \"+String(x));\n"
            "        }\n"
            "        match Float (x) {\n"
            "            standardOutput(\"zmienna jest floatem i wynosi: \"+String(x));\n"
            "        }\n"
            "        match none {\n"
            "            standardOutput(\"zmienna jest czymś innym\");\n"
            "        }\n"
            "    }\n"
            "}\n"
            "describe(32);\n"
            "describe(16);\n"
            "describe(22.38);\n"
            "mut para = 22, 38;\n"
            "describe(para);\n"
            "para = 21, 35;\n"
            "describe(para);\n"
            "describe(\"para\");";
    std::istringstream iss(code);

    LexerWithoutComments lexerWithoutComments(iss, errorHandler);
    MyLangParser parser(std::make_unique<LexerWithoutComments>(lexerWithoutComments), errorHandler);
    Program program = parser.parse();
    MyLangInterpreter interpreter(oss, iss, interpreterErrorHandler);
    interpreter.execute(program);
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(interpreterErrorOccurred);
    ASSERT_EQ(oss.str(), "match expression: 32, wartość x: 32\n"
                         "zmienna jest parzysta, x = 16\n"
                         "zmienna jest floatem i wynosi: 22.38\n"
                         "pierwszy element: 22, drugi element: 35\n"
                         "pierwszy element stały 21, drugi element stały 35\n"
                         "zmienna jest stringiem i wynosi: para\n");
}