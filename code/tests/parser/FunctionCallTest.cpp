#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(FunctionCallTest, ParseFunctionCallWithoutArgs) {
    Position position(1, 1);
    std::queue<Token> tokens({
         Token(TokenType::IDENTIFIER, "a", position),
         Token(TokenType::LEFT_BRACKET, position),
         Token(TokenType::RIGHT_BRACKET, position),
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
        program.accept(&visitor);
        std::string expected = "program {\n"
                               "  function call {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    args {\n"
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

TEST(FunctionCallTest, ParseFunctionCallWithOneArg) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "b", position),
        Token(TokenType::RIGHT_BRACKET, position),
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
        program.accept(&visitor);
        std::string expected = "program {\n"
                               "  function call {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    args {\n"
                               "      identifier {\n"
                               "        b\n"
                               "      }\n"
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

TEST(FunctionCallTest, ParseFunctionCallWithTwoArgs) {
    Position position(1, 1);
    std::queue<Token> tokens({
         Token(TokenType::IDENTIFIER, "a", position),
         Token(TokenType::LEFT_BRACKET, position),
         Token(TokenType::IDENTIFIER, "arg1", position),
         Token(TokenType::COMMA, position),
         Token(TokenType::IDENTIFIER, "arg2", position),
         Token(TokenType::RIGHT_BRACKET, position),
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
        program.accept(&visitor);
        std::string expected = "program {\n"
                               "  function call {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    args {\n"
                               "      identifier {\n"
                               "        arg1\n"
                               "      }\n"
                               "      identifier {\n"
                               "        arg2\n"
                               "      }\n"
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

TEST(FunctionCallTest, ParseFunctionCallWithCommaAfterArguments) {
    Position position(1, 1);
    Position errorPosition(1, 2);   // nie ma znaczenia jaka byle rożna od position
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "arg1", position),
        Token(TokenType::COMMA, position),
        Token(TokenType::IDENTIFIER, "arg2", position),
        Token(TokenType::COMMA, position),
        Token(TokenType::RIGHT_BRACKET, errorPosition),
        Token(TokenType::SEMICOLON, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::EXPRESSION_EXPECTED);
            ASSERT_EQ(position, errorPosition);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}