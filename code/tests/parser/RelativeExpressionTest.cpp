#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(RelativeExpressionTest, ParseIsExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::IS_KEYWORD, position),
        Token(TokenType::FLOAT_KEYWORD, position),
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      relative expression, type: IS {\n"
                               "        left {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          Typename Float\n"
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

TEST(RelativeExpressionTest, ParseGreaterThanExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::GREATER_THAN, position),
        Token(TokenType::IDENTIFIER, "y", position),
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      relative expression, type: GREATER {\n"
                               "        left {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          identifier {\n"
                               "            y\n"
                               "          }\n"
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

TEST(RelativeExpressionTest, ParseGreaterEqualExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::GREATER_OR_EQUAL, position),
        Token(TokenType::IDENTIFIER, "y", position),
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      relative expression, type: GREATER_EQUAL {\n"
                               "        left {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          identifier {\n"
                               "            y\n"
                               "          }\n"
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

TEST(RelativeExpressionTest, ParseLessEqualExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::LESS_OR_EQUAL, position),
        Token(TokenType::IDENTIFIER, "y", position),
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      relative expression, type: LESS_EQUAL {\n"
                               "        left {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          identifier {\n"
                               "            y\n"
                               "          }\n"
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
