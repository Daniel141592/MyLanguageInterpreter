#ifndef CODE_LEXERMOCK_H
#define CODE_LEXERMOCK_H

#include <queue>
#include <utility>

#include "../../../lexer/Lexer.h"

class LexerMock : public Lexer {
    std::queue<Token> tokens;
public:
    LexerMock(std::queue<Token> t);
    std::optional<Token> nextToken() override;
};

#endif //CODE_LEXERMOCK_H
