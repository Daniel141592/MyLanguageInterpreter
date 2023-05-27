#ifndef CODE_PARSER_H
#define CODE_PARSER_H

#include <functional>

#include "structure/Program.h"
#include "../Position.h"
#include "../ErrorType.h"
#include "../Token.h"
#include "../lexer/Lexer.h"


class Parser {
public:
    typedef std::function<void(Position, ErrorType)> HandlerType;
    ~Parser() = default;

    virtual Program parse() = 0;
};

#endif //CODE_PARSER_H
