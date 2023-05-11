#include <gtest/gtest.h>
#include <sstream>

#include "../lexer/MyLangLexer.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(LexerTests, PositionTest) {
    Position position;
    ASSERT_EQ(position.getLine(), 1);
    ASSERT_EQ(position.getColumn(), 1);
}

TEST(LexerTests, EOTTest) {
    std::istringstream iss("\t\tmut var = 7;");
    bool errorOccurred = false;
    MyLangLexer lexer(iss,  [&errorOccurred](Position p, ErrorType e){errorOccurred = true;});
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::END_OF_TEXT);
    ASSERT_FALSE(errorOccurred);
}

TEST(LexerTests, NextTokenWhenEOTAlreadyOccurred) {
    std::istringstream iss("mut var");
    bool errorOccurred = false;
    MyLangLexer lexer(iss,  [&errorOccurred](Position p, ErrorType e){errorOccurred = true;});
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::END_OF_TEXT);
    ASSERT_FALSE(errorOccurred);
}