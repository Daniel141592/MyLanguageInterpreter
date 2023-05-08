#include "Token.h"

Token::Token(TokenType t, std::string str, Position pos) : type(t), value(str), position(pos) {
    assert(t == TokenType::COMMENT || t == TokenType::STRING_LITERAL || t == TokenType::IDENTIFIER);
}

Token::Token(TokenType t, int num, Position pos) : type(t), value(num), position(pos) {
    assert(t == TokenType::INTEGER_VALUE);
}

Token::Token(TokenType t, double num, Position pos) : type(t), value(num), position(pos) {
    assert(t == TokenType::FLOAT_VALUE);
}

Token::Token(TokenType t, Position pos) :type(t), position(pos) {
    assert(t != TokenType::COMMENT && t != TokenType::STRING_LITERAL && t != TokenType::IDENTIFIER
           && t != TokenType::INTEGER_VALUE && t != TokenType::FLOAT_VALUE);
}

Token::Token() = default;

TokenType Token::getType() const {
    return type;
}

const Token::ValueType &Token::getValue() const {
    return value;
}

const Position &Token::getPosition() const {
    return position;
}
