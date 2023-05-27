#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(ParseBlockTest, ParseEmptyBlock) {
    Position position(1, 1);
    std::queue<Token> tokens({
         Token(TokenType::LEFT_PARENTHESIS, position),
         Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    try {
        auto onError = [&errorOccurred](Position position, ErrorType error) {
            errorOccurred = true;
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
        std::ostringstream oss;
        PrintVisitor visitor(oss);
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  block {\n"
                               "  }\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
        ASSERT_FALSE(errorOccurred);
    } catch (...) {
        errorOccurred = true;
    }
}

TEST(ParseBlockTest, NotClosedBlock) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::LEFT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::MISSING_PARENTHESIS);
            ASSERT_EQ(position, position);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}
