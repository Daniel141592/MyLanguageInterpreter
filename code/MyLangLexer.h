#ifndef CODE_MYLANGLEXER_H
#define CODE_MYLANGLEXER_H

#include <istream>
#include <functional>
#include <utility>
#include <cmath>
#include <optional>

#include "Lexer.h"
#include "ErrorType.h"

class MyLangLexer : public Lexer {
    typedef std::function<void(Position, ErrorType)> HandlerType;

    Token token;
    Position position;
    std::istream& is;
    HandlerType errorHandler;
    char currentChar{};
    std::string newLineSeq;

    bool nextCharacter();
    bool newLineSeqReached();
    void trySetNewlineSeq();

    std::optional<Token> tryBuildSimpleTokens();
    std::optional<Token> tryBuildNumber();
    std::optional<Token> tryBuildIdentifierOrKeyword();
    std::optional<Token> tryBuildComment();
    std::optional<Token> tryBuildString();
public:
    static std::unordered_map<std::string, TokenType> keywords;
    static std::unordered_map<char, char> specialChars;
    static std::unordered_map<char, TokenType> simpleTokens;
    static std::unordered_map<std::string, TokenType> twoCharactersTokens;
    const static int MAX_STRING_LITERAL_LENGTH = 2048;
    const static int MAX_IDENTIFIER_LENGTH = 2048;
    const static int MAX_COMMENT_LENGTH = 2048;

    static void initializeKeywordsAndSpecialChars();

    MyLangLexer(std::istream&, HandlerType);

    bool nextToken() override;
    Token getToken() const override;
};


#endif //CODE_MYLANGLEXER_H
