#ifndef CODE_LEXER_H
#define CODE_LEXER_H


#include <map>
#include <string>


#include "TokenType.h"
#include "Token.h"
#include "ErrorType.h"

class Lexer {
public:
    typedef std::function<void(Position, ErrorType)> HandlerType;
    virtual ~Lexer() = default;

    virtual bool nextToken() = 0;
    virtual Token getToken() const = 0;
};


#endif //CODE_LEXER_H