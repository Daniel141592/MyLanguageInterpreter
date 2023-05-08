#include <gtest/gtest.h>

#include "../MyLangLexer.h"

TEST(StringTest, BuildSimpleString) {
    std::istringstream iss("\"some value\"");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "some value");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildStringContainingEscapeChars) {
    std::istringstream iss("\"citation: \\\"some words\\\"\"");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "citation: \"some words\"");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildStringContainingEscapeChars2) {
    std::istringstream iss("\"text contains backslash\\\\\"");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "text contains backslash\\");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildStringContainingEscapeChars3) {
    std::istringstream iss("\"\\n\"");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value[0], '\n');
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildStringContainingEscapeChars4) {
    std::istringstream iss("\"\\b\\n\\f\\r\\t\"");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value[0], '\b');
    ASSERT_EQ(value[1], '\n');
    ASSERT_EQ(value[2], '\f');
    ASSERT_EQ(value[3], '\r');
    ASSERT_EQ(value[4], '\t');
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildStringContainingWrongEscapeChar) {
    std::istringstream iss("\"there is no '\\p' char\"");
    bool errorOccurred = false;
    bool unknownEscapeChar = false;
    MyLangLexer lexer(iss, [&errorOccurred, &unknownEscapeChar](Position p, ErrorType e){
        unknownEscapeChar = e == ErrorType::UnknownEscapeCharacter;
        errorOccurred = e != ErrorType::UnknownEscapeCharacter;
    });
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_TRUE(unknownEscapeChar);
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "there is no '' char");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildStringNotProperlyClosed) {
    std::istringstream iss("\"there is no end");
    bool errorOccurred = false;
    bool unexpectedEOT = false;
    MyLangLexer lexer(iss, [&errorOccurred, &unexpectedEOT](Position p, ErrorType e){
        unexpectedEOT = e == ErrorType::UnexpectedEndOfText;
        errorOccurred = e != ErrorType::UnexpectedEndOfText;
    });
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_TRUE(unexpectedEOT);
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "there is no end");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, BuildTooLongString) {
    std::stringstream stream;
    stream << "\"";
    for (int i = 0; i < MyLangLexer::MAX_STRING_LITERAL_LENGTH; ++i)
        stream << 'x';
    stream << "\"";
    bool errorOccurred = false;
    bool tooLongString = false;
    MyLangLexer lexer(stream, [&errorOccurred, &tooLongString](Position p, ErrorType e){
        tooLongString = e == ErrorType::TooLongStringLiteral;
        errorOccurred = e != ErrorType::TooLongStringLiteral;
    });
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_TRUE(tooLongString);
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_TRUE(value.size() == MyLangLexer::MAX_STRING_LITERAL_LENGTH);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(StringTest, EOTAfterBackslash) {
    std::istringstream iss("\"unexpected end\\");
    bool errorOccurred = false;
    bool unexpectedEOT = false;
    MyLangLexer lexer(iss, [&errorOccurred, &unexpectedEOT](Position p, ErrorType e){
        unexpectedEOT = e == ErrorType::UnexpectedEndOfText;
        errorOccurred = e != ErrorType::UnexpectedEndOfText;
    });
    Token token = *lexer.nextToken();
    std::string value = std::get<std::string>(token.getValue());
    ASSERT_TRUE(unexpectedEOT);
    ASSERT_EQ(token.getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "unexpected end");
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}
