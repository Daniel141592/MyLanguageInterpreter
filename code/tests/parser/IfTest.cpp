#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(IfTest, ParseEmptyIf) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "variable_containing_condition", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position),
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
                               "  if {\n"
                               "    condition {\n"
                               "      identifier {\n"
                               "        variable_containing_condition\n"
                               "      }\n"
                               "    }\n"
                               "    block {\n"
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

TEST(IfTest, ParseSimpleIf) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "variable_containing_condition", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::SEMICOLON, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
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
                               "  if {\n"
                               "    condition {\n"
                               "      identifier {\n"
                               "        variable_containing_condition\n"
                               "      }\n"
                               "    }\n"
                               "    block {\n"
                               "      function call {\n"
                               "        name {\n"
                               "          identifier {\n"
                               "            a\n"
                               "          }\n"
                               "        }\n"
                               "        args {\n"
                               "        }\n"
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

TEST(IfTest, ParseIfElse) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position),
        Token(TokenType::ELSE_KEYWORD, position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
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
                               "  if {\n"
                               "    condition {\n"
                               "      identifier {\n"
                               "        x\n"
                               "      }\n"
                               "    }\n"
                               "    block {\n"
                               "    }\n"
                               "    else {\n"
                               "      block {\n"
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

TEST(IfTest, ParseIfWithoutExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IF_KEYWORD, position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::SEMICOLON, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&errorOccurred](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::EXPRESSION_EXPECTED);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}

TEST(IfTest, ParseIfWithoutBlock) {
    Position position(1, 1);
    Position badPosition(3, 3);
    std::queue<Token> tokens({
        Token(TokenType::IF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "variable_containing_condition", position),
        Token(TokenType::END_OF_TEXT, badPosition)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::BLOCK_EXPECTED);
            ASSERT_EQ(position, badPosition);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}
