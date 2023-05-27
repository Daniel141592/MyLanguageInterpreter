#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(FunctionDeclarationTest, ParseFunctionDeclarationWithoutArgsAndBody) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::FUNC_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::RIGHT_BRACKET, position),
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
        program.accept(&visitor);
        std::string expected = "program {\n"
                               "  function {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    arguments {\n"
                               "    }\n"
                               "    block {\n"
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

TEST(FunctionDeclarationTest, ParseFunctionDeclarationWithoutBody) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::FUNC_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::REF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "b", position),
        Token(TokenType::RIGHT_BRACKET, position),
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
        program.accept(&visitor);
        std::string expected = "program {\n"
                               "  function {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    arguments {\n"
                               "      argument ref {\n"
                               "        identifier {\n"
                               "          b\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "    block {\n"
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

TEST(FunctionDeclarationTest, ParseFunctionDeclaration) {
    Position position(1, 1);
    std::queue<Token> tokens({
        Token(TokenType::FUNC_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::REF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "b", position),
        Token(TokenType::RIGHT_BRACKET, position),
        Token(TokenType::LEFT_PARENTHESIS, position),
        Token(TokenType::IDENTIFIER, "c", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::SEMICOLON, position),
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
        program.accept(&visitor);
        std::string expected = "program {\n"
                               "  function {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        a\n"
                               "      }\n"
                               "    }\n"
                               "    arguments {\n"
                               "      argument ref {\n"
                               "        identifier {\n"
                               "          b\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "    block {\n"
                               "      assign {\n"
                               "        name {\n"
                               "          identifier {\n"
                               "            c\n"
                               "          }\n"
                               "        }\n"
                               "        expression {\n"
                               "          integer constant: 5\n"
                               "        }\n"
                               "      }\n"
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

TEST(FunctionDeclarationTest, ParseFunctionDeclarationWithoutCloseBracket) {
    Position position(1, 1);
    Position badPosition(5, 8);
    std::queue<Token> tokens({
        Token(TokenType::FUNC_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "a", position),
        Token(TokenType::LEFT_BRACKET, position),
        Token(TokenType::REF_KEYWORD, position),
        Token(TokenType::IDENTIFIER, "b", position),
        Token(TokenType::LEFT_PARENTHESIS, badPosition),
        Token(TokenType::IDENTIFIER, "c", position),
        Token(TokenType::ASSIGN, position),
        Token(TokenType::INTEGER_VALUE, 5, position),
        Token(TokenType::SEMICOLON, position),
        Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::BRACKET_EXPECTED);
            ASSERT_EQ(position, badPosition);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(errorOccurred);
    ASSERT_TRUE(exceptionThrown);
}