#include <gtest/gtest.h>
#include <sstream>

#include "../MyLangLexer.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(LexerTests, PositionTest) {
    Position position;
    ASSERT_EQ(position.getLine(), 1);
    ASSERT_EQ(position.getColumn(), 1);
}

TEST(LexerTests, KeywordMapTest) {
    std::istringstream iss("");
    MyLangLexer::initializeKeywordsAndSpecialChars();
    ASSERT_EQ(MyLangLexer::keywords["mut"], TokenType::MUT);
}
