#include <gtest/gtest.h>

#include "../MyLangLexer.h"

TEST(NewLineTests, BasicNewLineCharacter) {
    std::istringstream iss("first line\nsecond line");
    auto onError = [](Position position, ErrorType error) {};
    MyLangLexer lexer(iss, onError);
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();  // 3rd token which should be identifier 'second'
    ASSERT_EQ(lexer.getToken().getPosition().getColumn(), 1);
    ASSERT_EQ(lexer.getToken().getPosition().getLine(), 2);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_EQ(std::get<std::string>(lexer.getToken().getValue()), "second");
}

TEST(NewLineTests, LFCRCharacter) {
    std::istringstream iss("first line\n\rsecond line");
    auto onError = [](Position position, ErrorType error) {};
    MyLangLexer lexer(iss, onError);
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();  // 3rd token which should be identifier 'second'
    ASSERT_EQ(lexer.getToken().getPosition().getColumn(), 1);
    ASSERT_EQ(lexer.getToken().getPosition().getLine(), 2);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_EQ(std::get<std::string>(lexer.getToken().getValue()), "second");
}

TEST(NewLineTests, CRLFCharacter) {
    std::istringstream iss("first line\r\nsecond line");
    auto onError = [](Position position, ErrorType error) {};
    MyLangLexer lexer(iss, onError);
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();  // 3rd token which should be identifier 'second'
    ASSERT_EQ(lexer.getToken().getPosition().getColumn(), 1);
    ASSERT_EQ(lexer.getToken().getPosition().getLine(), 2);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_EQ(std::get<std::string>(lexer.getToken().getValue()), "second");
}

TEST(NewLineTests, OnlyCRCharacter) {
    std::istringstream iss("first line\rsecond line");
    auto onError = [](Position position, ErrorType error) {};
    MyLangLexer lexer(iss, onError);
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();  // 3rd token which should be identifier 'second'
    ASSERT_EQ(lexer.getToken().getPosition().getColumn(), 1);
    ASSERT_EQ(lexer.getToken().getPosition().getLine(), 2);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_EQ(std::get<std::string>(lexer.getToken().getValue()), "second");
}

TEST(NewLineTests, InconsistentNewlineSequence) {
    std::istringstream iss("first line\r\nsecond_line\nthird_line");
    bool inconsistentNl = false;
    auto onError = [&inconsistentNl](Position position, ErrorType error) {
        inconsistentNl = error == ErrorType::InconsistentNewlineSequence;
    };
    MyLangLexer lexer(iss, onError);
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();  //4th token which should be identifier 'third_line'
    ASSERT_EQ(lexer.getToken().getPosition().getColumn(), 1);
    ASSERT_EQ(lexer.getToken().getPosition().getLine(), 3);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_EQ(std::get<std::string>(lexer.getToken().getValue()), "third_line");
    ASSERT_TRUE(inconsistentNl);
}

TEST(NewLineTests, ConsistentNewlineSequences) {
    std::istringstream iss("first line\r\nsecond_line\r\nthird_line");
    bool inconsistentNl = false;
    auto onError = [&inconsistentNl](Position position, ErrorType error) {
        inconsistentNl = error == ErrorType::InconsistentNewlineSequence;
    };
    MyLangLexer lexer(iss, onError);
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();
    lexer.nextToken();  //4th token which should be identifier 'third_line'
    ASSERT_FALSE(inconsistentNl);
}