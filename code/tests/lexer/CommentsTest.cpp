#include <gtest/gtest.h>

#include "../../lexer/MyLangLexer.h"

TEST(CommentsTest, BuildSimpleComment) {
    std::istringstream iss("$comment");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::COMMENT);
    ASSERT_EQ(value, "comment");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(CommentsTest, BuildCommentsToEndOfLine) {
    std::istringstream iss("$comment about some code\nfunc fibonacci");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::COMMENT);
    ASSERT_EQ(value, "comment about some code");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::FUNC_KEYWORD);
    ASSERT_TRUE(token.getPosition() == Position(1, 2));
    ASSERT_FALSE(errorOccurred);
}

TEST(CommentsTest, BuildCommentsContainingKeywords) {
    std::istringstream iss("$ comment if func\nfibonacci");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::COMMENT);
    ASSERT_EQ(value, " comment if func");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::IDENTIFIER);
    ASSERT_TRUE(token.getPosition() == Position(1, 2));
    ASSERT_FALSE(errorOccurred);
}

TEST(CommentsTest, BuildTooLongComment) {
    std::stringstream stream("");
    stream << "$";
    for (int i = 0; i < MyLangLexer::MAX_COMMENT_LENGTH; ++i)
        stream << "x";
    stream << "comment";
    bool errorOccurred = false;
    bool tooLongComment = false;
    MyLangLexer lexer(stream, [&errorOccurred, &tooLongComment](Position p, ErrorType e){
        tooLongComment = e == ErrorType::TooLongComment;
        errorOccurred = e != ErrorType::TooLongComment;
    });
    Token token = *lexer.nextToken();
    size_t commentLength = std::get<std::string>(token.getValue()).size();
    ASSERT_TRUE(tooLongComment);
    ASSERT_EQ(token.getType(), TokenType::COMMENT);
    ASSERT_TRUE(commentLength == MyLangLexer::MAX_COMMENT_LENGTH);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}
