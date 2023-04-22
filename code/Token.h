#ifndef CODE_TOKEN_H
#define CODE_TOKEN_H

#include <string>
#include <variant>
#include <utility>

#include "TokenType.h"
#include "Position.h"

class Token {
    typedef std::variant<std::string, int, double> ValueType;

    TokenType type;
    ValueType value;
    Position position;

public:
    Token();
    Token(TokenType, ValueType, Position);
    Token(TokenType, Position);

    TokenType getType() const;

    const ValueType &getValue() const;

    const Position &getPosition() const;
};


#endif //CODE_TOKEN_H
