#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(ExpressionTest, ParseOrExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::OR, position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      or expression {\n"
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

TEST(ExpressionTest, ParseAndExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::AND, position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      and expression {\n"
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

TEST(ExpressionTest, ParseAndExpressionOrAndExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::AND, position),
        Token(TokenType::IDENTIFIER, "y", position),
        Token(TokenType::OR, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::AND, position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      or expression {\n"
                               "        left {\n"
                               "          and expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                x\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              identifier {\n"
                               "                y\n"
                               "              }\n"
                               "            }\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          and expression {\n"
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

TEST(ExpressionTest, ParseAndExpressionWithBrackets) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::AND, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "y", position),
        Token(TokenType::OR, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::AND, position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      and expression {\n"
                               "        left {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          or expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                y\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              and expression {\n"
                               "                left {\n"
                               "                  identifier {\n"
                               "                    a\n"
                               "                  }\n"
                               "                }\n"
                               "                right {\n"
                               "                  identifier {\n"
                               "                    b\n"
                               "                  }\n"
                               "                }\n"
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

TEST(ExpressionTest, NegatedExpressionTest) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::NEGATION, position),
        Token(TokenType::IDENTIFIER, "x", position),
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      negated expression {\n"
                               "        identifier {\n"
                               "          x\n"
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

TEST(ExpressionTest, ParseArithmeticExpresion) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::ASTERISK, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::PLUS, position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      add expression {\n"
                               "        left {\n"
                               "          multiply expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                x\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              integer constant: 5\n"
                               "            }\n"
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

TEST(ExpressionTest, ParseArithmeticExpresionWithBrackets) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::ASTERISK, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::PLUS, position),
        Token(TokenType::IDENTIFIER, "y", position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      multiply expression {\n"
                               "        left {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          add expression {\n"
                               "            left {\n"
                               "              integer constant: 5\n"
                               "            }\n"
                               "            right {\n"
                               "              identifier {\n"
                               "                y\n"
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

TEST(ExpressionTest, ParseExpressionWithArithmeticAndLogicalParts) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::PLUS, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::AND, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "y", position),
        Token(TokenType::OR, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::AND, position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      and expression {\n"
                               "        left {\n"
                               "          add expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                x\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              integer constant: 5\n"
                               "            }\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          or expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                y\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              and expression {\n"
                               "                left {\n"
                               "                  identifier {\n"
                               "                    a\n"
                               "                  }\n"
                               "                }\n"
                               "                right {\n"
                               "                  identifier {\n"
                               "                    b\n"
                               "                  }\n"
                               "                }\n"
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

TEST(ExpressionTest, ParseCastExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::FLOAT_KEYWORD, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "x", position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      cast expression {\n"
                               "        type {\n"
                               "          float\n"
                               "        }\n"
                               "        expression {\n"
                               "          identifier {\n"
                               "            x\n"
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

TEST(ExpressionTest, ParseMutualAndExpressions) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::AND, position),
        Token(TokenType::IDENTIFIER, "y", position),
        Token(TokenType::AND, position),
        Token(TokenType::IDENTIFIER, "z", position),
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        var\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      and expression {\n"
                               "        left {\n"
                               "          and expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                x\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              identifier {\n"
                               "                y\n"
                               "              }\n"
                               "            }\n"
                               "          }\n"
                               "        }\n"
                               "        right {\n"
                               "          identifier {\n"
                               "            z\n"
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

TEST(ExpressionTest, AndExpressionWithoutRightPart) {
    Position position(1, 1);
    Position badPosition(2, 3);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "var", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::AND, position),
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