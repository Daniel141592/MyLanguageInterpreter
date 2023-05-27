#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"
#include "../../lexer/MyLangLexer.h"

TEST(IntegrationWithLexerTest, IntegrationAssignTest) {
    std::istringstream iss("a = 3;");
    bool errorOccurred = false;
    auto onError = [&](Position position, ErrorType error) {
        errorOccurred = true;
    };
    try {
        MyLangLexer lexer(iss, onError);
        MyLangParser parser(std::make_unique<MyLangLexer>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      integer constant: 3\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
    } catch (...) {
        errorOccurred = true;
    }
    ASSERT_FALSE(errorOccurred);
}

TEST(IntegrationWithLexerTest, IntegrationFunctionCallTest) {
    std::istringstream iss("standardOutput(\"text\");");
    bool errorOccurred = false;
    auto onError = [&](Position position, ErrorType error) {
        errorOccurred = true;
    };
    try {
        MyLangLexer lexer(iss, onError);
        MyLangParser parser(std::make_unique<MyLangLexer>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  function call {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        standardOutput\n"
                               "      }\n"
                               "    }\n"
                               "    args {\n"
                               "      string constant: text\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
    } catch (...) {
        errorOccurred = true;
    }
    ASSERT_FALSE(errorOccurred);
}
