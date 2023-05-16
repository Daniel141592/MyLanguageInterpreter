#include "LexerMock.h"

LexerMock::LexerMock(std::queue<Token> t) : tokens(std::move(t)) {

}

std::optional<Token> LexerMock::nextToken() {
    if (tokens.empty())
        return Token(TokenType::END_OF_TEXT, Position(1, 1));
    Token token = tokens.front();
    tokens.pop();
    return token;
}
