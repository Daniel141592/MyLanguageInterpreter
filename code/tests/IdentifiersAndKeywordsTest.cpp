#include <gtest/gtest.h>

#include "../MyLangLexer.h"

TEST(IdentifiersAndKeywords, BuildSimpleIdentifier) {
    std::istringstream iss("nameOfVariable");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(value, "nameOfVariable");
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(IdentifiersAndKeywords, BuildIdentfierWithDigits) {
    std::istringstream iss("name123");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(value, "name123");
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(IdentifiersAndKeywords, IdentifierCannotStartWithDigit) {
    std::istringstream iss("123name123");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::INTEGER_VALUE);
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(value, "name123");
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(4, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(IdentifiersAndKeywords, TryToBuildTooLongIdentifier) {
    std::stringstream stream;
    for (int i = 0; i < MyLangLexer::MAX_IDENTIFIER_LENGTH; ++i)
        stream << 'x';
    stream << "_var";
    bool errorOccurred = false;
    bool tooLongId = false;
    MyLangLexer lexer(stream, [&errorOccurred, &tooLongId](Position p, ErrorType e){
        tooLongId = e == ErrorType::TooLongIdentifier;
        errorOccurred = e != ErrorType::TooLongIdentifier;
    });
    lexer.nextToken();

    ASSERT_TRUE(tooLongId);
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    size_t idLength = std::get<std::string>(lexer.getToken().getValue()).size();
    ASSERT_TRUE(idLength == MyLangLexer::MAX_IDENTIFIER_LENGTH);
    ASSERT_FALSE(errorOccurred);
}

TEST(IdentifiersAndKeywords, BuildIdentifierStartingWithKeyword) {
    std::istringstream iss("mutant");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(value, "mutant");
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IDENTIFIER);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(IdentifiersAndKeywords, BuildSimpleKeywords) {
    std::istringstream iss("Int Float\nString\nfunc\nloop\nif\nreturn\nmut\nelse\npattern\nmatch\nis\nnone\nref");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});

    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::INT_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::FLOAT_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(5, 1));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::STRING_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 2));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::FUNC_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 3));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::LOOP_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 4));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IF_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 5));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::RETURN_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 6));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::MUT_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 7));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::ELSE_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 8));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::PATTERN_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 9));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::MATCH_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 10));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::IS_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 11));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::NONE_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 12));
    lexer.nextToken();
    ASSERT_EQ(lexer.getToken().getType(), TokenType::REF_KEYWORD);
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 13));

    ASSERT_FALSE(errorOccurred);
}
