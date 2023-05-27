#include <gtest/gtest.h>

#include "../../lexer/MyLangLexer.h"

TEST(SimpleTokenTest, BuildOperators) {
    std::istringstream iss("+-*;");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::PLUS);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::MINUS);
    ASSERT_TRUE(token.getPosition() == Position(2, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::ASTERISK);
    ASSERT_TRUE(token.getPosition() == Position(3, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::SEMICOLON);
    ASSERT_TRUE(token.getPosition() == Position(4, 1));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOperatorsThatStartSameAsOthers) {
    std::istringstream iss("/=<>!");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::DIVISION);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::ASSIGN);
    ASSERT_TRUE(token.getPosition() == Position(2, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::LESS_THAN);
    ASSERT_TRUE(token.getPosition() == Position(3, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::GREATER_THAN);
    ASSERT_TRUE(token.getPosition() == Position(4, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::NEGATION);
    ASSERT_TRUE(token.getPosition() == Position(5, 1));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOperatorsTwoCharactersOperators) {
    std::istringstream iss("//==<=>=!=");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::INT_DIVISION);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(3, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::LESS_OR_EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(5, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::GREATER_OR_EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(7, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::NOT_EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(9, 1));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOnlyDivide) {
    std::istringstream iss("/");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::DIVISION);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOperatorsInManyLines) {
    std::istringstream iss("/\n==\n<=\n>>=\n!=");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::DIVISION);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(1, 2));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::LESS_OR_EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(1, 3));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::GREATER_THAN);
    ASSERT_TRUE(token.getPosition() == Position(1, 4));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::GREATER_OR_EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(2, 4));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::NOT_EQUAL);
    ASSERT_TRUE(token.getPosition() == Position(1, 5));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildBrackets) {
    std::istringstream iss(" (\n\n )");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::LEFT_BRACKET);
    ASSERT_TRUE(token.getPosition() == Position(2, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::RIGHT_BRACKET);
    ASSERT_TRUE(token.getPosition() == Position(2, 3));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildParenthesis) {
    std::istringstream iss(" {\n\n }");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::LEFT_PARENTHESIS);
    ASSERT_TRUE(token.getPosition() == Position(2, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::RIGHT_PARENTHESIS);
    ASSERT_TRUE(token.getPosition() == Position(2, 3));

    ASSERT_FALSE(errorOccurred);
}
