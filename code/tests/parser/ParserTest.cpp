#include <gtest/gtest.h>

#include "../../parser/MyLangParser.h"
#include "../../parser/PrintVisitor.h"
#include "LexerMock/LexerMock.h"

TEST(ParserTests, ComplexTest) {
    Position position(1, 1);    // nie ma znaczenia dla testu
    std::queue<Token> tokens({
            Token(TokenType::FUNC_KEYWORD, position),
            Token(TokenType::IDENTIFIER, "function", position),
            Token(TokenType::LEFT_BRACKET, position),
            Token(TokenType::IDENTIFIER, "a", position),
            Token(TokenType::COMMA, position),
            Token(TokenType::IDENTIFIER, "b", position),
            Token(TokenType::RIGHT_BRACKET, position),
            Token(TokenType::LEFT_PARENTHESIS, position),
            Token(TokenType::RETURN_KEYWORD, position),
            Token(TokenType::IDENTIFIER, "a", position),
            Token(TokenType::PLUS, position),
            Token(TokenType::IDENTIFIER, "b", position),
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
        program.accept(visitor);
        std::string expected = "program {\n"
                               "  function {\n"
                               "    name {\n"
                               "      identifier {\n"
                               "        function\n"
                               "      }\n"
                               "    }\n"
                               "    arguments {\n"
                               "      argument {\n"
                               "        identifier {\n"
                               "          a\n"
                               "        }\n"
                               "      }\n"
                               "      argument {\n"
                               "        identifier {\n"
                               "          b\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "    block {\n"
                               "      return {\n"
                               "        expression {\n"
                               "          add expression {\n"
                               "            left {\n"
                               "              identifier {\n"
                               "                a\n"
                               "              }\n"
                               "            }\n"
                               "            right {\n"
                               "              identifier {\n"
                               "                b\n"
                               "              }\n"
                               "            }\n"
                               "          }\n"
                               "        }\n"
                               "      }\n"
                               "    }\n"
                               "  }\n"
                               "}\n";
        std::string result = oss.str();
        ASSERT_EQ(result, expected);
        ASSERT_FALSE(errorOccurred);
    } catch (...) {
        errorOccurred = true;
    }
}

TEST(ParserTests, IncorrectReturn) {
    Position position(1, 1);
    Position incorrectTokenPosition(10, 10); // konkretna wartość nie ma znaczenia
    std::queue<Token> tokens({  // to samo co w teście wyżej, ale z usuniętym znakiem '+'
         Token(TokenType::FUNC_KEYWORD, position),
         Token(TokenType::IDENTIFIER, "function", position),
         Token(TokenType::LEFT_BRACKET, position),
         Token(TokenType::IDENTIFIER, "a", position),
         Token(TokenType::COMMA, position),
         Token(TokenType::IDENTIFIER, "b", position),
         Token(TokenType::RIGHT_BRACKET, position),
         Token(TokenType::LEFT_PARENTHESIS, position),
         Token(TokenType::RETURN_KEYWORD, position),
         Token(TokenType::IDENTIFIER, "a", position),
         Token(TokenType::IDENTIFIER, "b", incorrectTokenPosition),
         Token(TokenType::SEMICOLON, position),
         Token(TokenType::RIGHT_PARENTHESIS, position)
    });
    LexerMock lexer(tokens);
    bool errorOccurred = false;
    bool exceptionThrown = false;
    try {
        auto onError = [&](Position position, ErrorType error) {
            errorOccurred = true;
            ASSERT_EQ(error, ErrorType::MISSING_SEMICOLON);
            ASSERT_EQ(position, incorrectTokenPosition);
        };
        MyLangParser parser(std::make_unique<LexerMock>(lexer), onError);
        Program program = parser.parse();
    } catch (...) {
        exceptionThrown = true;
    }
    ASSERT_TRUE(exceptionThrown);
}
