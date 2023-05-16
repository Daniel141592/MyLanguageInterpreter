#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(PatternTest, EmptyPatternTest) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::PATTERN_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "zmienna", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
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
                               "  pattern {\n"
                               "    expression {\n"
                               "      identifier {\n"
                               "        zmienna\n"
                               "      }\n"
                               "    }\n"
                               "    matches {\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        ASSERT_EQ(expected, oss.str());
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(exceptionThrown);
}

TEST(PatternTest, SimplePatternMatchTest) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::PATTERN_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "zmienna", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::MATCH_KEYWORD, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
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
                               "  pattern {\n"
                               "    expression {\n"
                               "      identifier {\n"
                               "        zmienna\n"
                               "      }\n"
                               "    }\n"
                               "    matches {\n"
                               "      match expression {\n"
                               "        expression {\n"
                               "          integer constant: 5\n"
                               "        }\n"
                               "        identifier {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        block {\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        ASSERT_EQ(expected, oss.str());
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(exceptionThrown);
}

TEST(PatternTest, PatternMatchExpressionTest) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::PATTERN_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "zmienna", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::MATCH_KEYWORD, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::PLUS, position),
        Token(TokenType::INTEGER_VALUE, 3, position),
        Token(TokenType::ASTERISK, position),
        Token(TokenType::INTEGER_VALUE, 7, position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
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
                               "  pattern {\n"
                               "    expression {\n"
                               "      identifier {\n"
                               "        zmienna\n"
                               "      }\n"
                               "    }\n"
                               "    matches {\n"
                               "      match expression {\n"
                               "        expression {\n"
                               "          add expression {\n"
                               "            left {\n"
                               "              integer constant: 5\n"
                               "            }\n"
                               "            right {\n"
                               "              multiply expression {\n"
                               "                left {\n"
                               "                  integer constant: 3\n"
                               "                }\n"
                               "                right {\n"
                               "                  integer constant: 7\n"
                               "                }\n"
                               "              }\n"
                               "            }\n"
                               "          }\n"
                               "        }\n"
                               "        identifier {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        block {\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        ASSERT_EQ(expected, oss.str());
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(exceptionThrown);
}

TEST(PatternTest, PatternMatchPairTest) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::PATTERN_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "zmienna", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::MATCH_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "x", position),
        Token(TokenType::COMMA, position),
        Token(TokenType::IDENTIFIER, "y", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
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
                               "  pattern {\n"
                               "    expression {\n"
                               "      identifier {\n"
                               "        zmienna\n"
                               "      }\n"
                               "    }\n"
                               "    matches {\n"
                               "      match pair {\n"
                               "        first {\n"
                               "          identifier {\n"
                               "            x\n"
                               "          }\n"
                               "        }\n"
                               "        second {\n"
                               "          identifier {\n"
                               "            y\n"
                               "          }\n"
                               "        }\n"
                               "        block {\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        ASSERT_EQ(expected, oss.str());
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(exceptionThrown);
}

TEST(PatternTest, PatternMatchNoneTest) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::PATTERN_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "zmienna", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::MATCH_KEYWORD, position),
        Token(TokenType::NONE_KEYWORD, position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
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
                               "  pattern {\n"
                               "    expression {\n"
                               "      identifier {\n"
                               "        zmienna\n"
                               "      }\n"
                               "    }\n"
                               "    matches {\n"
                               "      match none {\n"
                               "        block {\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        ASSERT_EQ(expected, oss.str());
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_FALSE(errorOccurred);
    ASSERT_FALSE(exceptionThrown);
}

TEST(PatternTest, PatternMatchWithoutExpression) {
    Position position(1, 1);
    Position badPosition(5, 5); // dokładna wartość bez znaczenia
    std::queue<Token> tokens({
        Token(TokenType::PATTERN_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "zmienna", position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::MATCH_KEYWORD, position),
        Token(TokenType::LEFT_PARENTHESIS, badPosition),
        Token(TokenType::RIGHT_PARENTHESIS, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::INVALID_MATCH_SYNTAX);
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
