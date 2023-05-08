#ifndef CODE_MYLANGLEXER_H
#define CODE_MYLANGLEXER_H

#include <istream>
#include <functional>
#include <utility>
#include <cmath>
#include <optional>
#include <climits>

#include "Lexer.h"
#include "ErrorType.h"

class MyLangLexer : public Lexer {
    Position position;
    std::istream& is;
    HandlerType errorHandler;
    char currentChar{};
    std::string newLineSeq;

    bool nextCharacter();
    bool newLineSeqReached();
    void trySetNewlineSeq();

    std::optional<Token> tryBuildEOT();
    std::optional<Token> tryBuildSimpleTokens();
    std::optional<Token> tryBuildNumber();
    std::optional<Token> tryBuildIdentifierOrKeyword();
    std::optional<Token> tryBuildComment();
    std::optional<Token> tryBuildString();
public:
    const static int MAX_STRING_LITERAL_LENGTH = 2048;
    const static int MAX_IDENTIFIER_LENGTH = 2048;
    const static int MAX_COMMENT_LENGTH = 2048;

    MyLangLexer(std::istream&, HandlerType);

    std::optional<Token> nextToken() override;
};


#endif //CODE_MYLANGLEXER_H
