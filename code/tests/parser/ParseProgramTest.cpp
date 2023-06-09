#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(ParseProgramTest, ParseEmptyProgram) {
    std::queue<Token> tokens;
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    try {
        auto onError = [&errorOccurred](Position position, ErrorType error) {
            errorOccurred = true;
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
        std::string expected = "program {\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
        ASSERT_FALSE(errorOccurred);
    } catch (...) {
        errorOccurred = true;
    }
}

TEST(ParseProgramTest, ParseSimpleProgram) {
    Position position(1, 1);    // nie ma znaczenia dla testu
    std::queue<Token> tokens({
        Token(TokenType::MUT_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::SEMICOLON, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    try {
        auto onError = [&errorOccurred](Position position, ErrorType error) {
            errorOccurred = true;
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  variable declaration {\n"
                               "    mutable: true\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
        ASSERT_FALSE(errorOccurred);
    } catch (...) {
        errorOccurred = true;
    }
    ASSERT_FALSE(errorOccurred);
}
