#include <gtest/gtest.h>

#include "../MyLangLexer.h"

TEST(SimpleTokenTest, BuildOperators) {
    std::istringstream iss("+-*;");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::PLUS);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::MINUS);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::ASTERISK);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(3, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::SEMICOLON);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(4, 1));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOperatorsThatStartSameAsOthers) {
    std::istringstream iss("/=<>!");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::DIVISION);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::ASSIGN);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::LESS_THAN);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(3, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::GREATER_THAN);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(4, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::NEGATION);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(5, 1));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOperatorsTwoCharactersOperators) {
    std::istringstream iss("//==<=>=!=");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::INT_DIVISION);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(3, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::LESS_OR_EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(5, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::GREATER_OR_EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(7, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::NOT_EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(9, 1));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOnlyDivide) {
    std::istringstream iss("/");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::DIVISION);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildOperatorsInManyLines) {
    std::istringstream iss("/\n==\n<=\n>>=\n!=");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::DIVISION);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 2));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::LESS_OR_EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 3));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::GREATER_THAN);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 4));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::GREATER_OR_EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 4));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::NOT_EQUAL);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 5));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildBrackets) {
    std::istringstream iss(" (\n\n )");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::LEFT_BRACKET);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::RIGHT_BRACKET);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 3));

    ASSERT_FALSE(errorOccurred);
}

TEST(SimpleTokenTest, BuildParenthesis) {
    std::istringstream iss(" {\n\n }");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::LEFT_PARENTHESIS);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::RIGHT_PARENTHESIS);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(2, 3));

    ASSERT_FALSE(errorOccurred);
}
