#include "Token.h"

Token::Token(TokenType t, Token::ValueType val, Position pos) : type(t), value(std::move(val)), position(pos) {

}

Token::Token(TokenType t, Position pos) :type(t), position(pos) {

}

Token::Token() {

}

TokenType Token::getType() const {
    return type;
}

const Token::ValueType &Token::getValue() const {
    return value;
}

const Position &Token::getPosition() const {
    return position;
}
