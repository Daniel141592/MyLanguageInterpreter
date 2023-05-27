#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(ParseAssignTest, ParseAssign) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::INTEGER_VALUE, 3, position),
        Token(TokenType::SEMICOLON, position)
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
                               "  assign {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    expression {\n"
                               "      integer constant: 3\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
    } catch (...) {
        errorOccurred = true;
    }
    ASSERT_FALSE(errorOccurred);
}

TEST(ParseAssignTest, AssignWithoutExpression) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::SEMICOLON, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::EXPRESSION_EXPECTED);
            ASSERT_EQ(position, position);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}

TEST(ParseAssignTest, AssignWithoutSemicolon) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::INTEGER_VALUE, 3, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::MISSING_SEMICOLON);
            ASSERT_EQ(position, position);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_FALSE(exceptionThrown);
}
