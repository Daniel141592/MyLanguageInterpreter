#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(PairTest, ParseSimplePair) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::COMMA, position),
        Token(TokenType::IDENTIFIER, "b", position),
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
                               "      pair {\n"
                               "        first {\n"
                               "          identifier {\n"
                               "            a\n"
                               "          }\n"
                               "        }\n"
                               "        second {\n"
                               "          identifier {\n"
                               "            b\n"
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

TEST(PairTest, ParsePairWithNumericExpressions) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::PLUS, position),
        Token(TokenType::IDENTIFIER, "b", position),
        Token(TokenType::COMMA, position),
        Token(TokenType::IDENTIFIER, "c", position),
        Token(TokenType::ASTERISK, position),
        Token(TokenType::IDENTIFIER, "d", position),
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
                               "      pair {\n"
                               "        first {\n"
                               "          add expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                a\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              identifier {\n"
                               "                b\n"
                               "              }\n"
                               "            }\n"
                               "          }\n"
                               "        }\n"
                               "        second {\n"
                               "          multiply expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                c\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              identifier {\n"
                               "                d\n"
                               "              }\n"
                               "            }\n"
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

TEST(PairTest, ParsePairWithoutSecondElement) {
    Position position(1, 1);
    Position badPosition(8, 21);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::COMMA, position),
        Token(TokenType::SEMICOLON, badPosition)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::EXPRESSION_EXPECTED);
            ASSERT_EQ(position, badPosition);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();

    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}

TEST(PairTest, ParsePairFieldAccess) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::DOT, position),
        Token(TokenType::IDENTIFIER, "first", position),
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
                               "      field {\n"
                               "        .first\n"
                               "        expression {\n"
                               "          identifier {\n"
                               "            a\n"
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

TEST(PairTest, ParsePairFieldAccess2) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::DOT, position),
        Token(TokenType::IDENTIFIER, "second", position),
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
                               "      field {\n"
                               "        .second\n"
                               "        expression {\n"
                               "          identifier {\n"
                               "            a\n"
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

TEST(PairTest, ParsePairBadFieldAccess) {
    Position position(1, 1);
    Position badPosition(2, 35);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::DOT, position),
        Token(TokenType::IDENTIFIER, "third", badPosition),
        Token(TokenType::SEMICOLON, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::FIRST_OR_SECOND_EXPECTED);
            ASSERT_EQ(position, badPosition);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}
