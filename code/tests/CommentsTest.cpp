#include <gtest/gtest.h>

#include "../MyLangLexer.h"

TEST(CommentsTest, BuildSimpleComment) {
    std::istringstream iss("$comment");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(lexer.getToken().getType(), TokenType::COMMENT);
    ASSERT_EQ(value, "comment");
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(CommentsTest, BuildCommentsToEndOfLine) {
    std::istringstream iss("$comment about some code\nfunc fibonacci");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(lexer.getToken().getType(), TokenType::COMMENT);
    ASSERT_EQ(value, "comment about some code");
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::FUNC_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 2));
    ASSERT_FALSE(errorOccurred);
}

TEST(CommentsTest, BuildCommentsContainingKeywords) {
    std::istringstream iss("$ comment if func\nfibonacci");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(lexer.getToken().getType(), TokenType::COMMENT);
    ASSERT_EQ(value, " comment if func");
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 2));
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
    lexer.nextToken();
    size_t commentLength = std::get<std::string>(lexer.getToken().getValue()).size();
    ASSERT_TRUE(tooLongComment);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::COMMENT);
    ASSERT_TRUE(commentLength == MyLangLexer::MAX_COMMENT_LENGTH);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}
