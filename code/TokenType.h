#ifndef CODE_TOKENTYPE_H
#define CODE_TOKENTYPE_H


enum TokenType {
    END_OF_TEXT,
    MUT,
    COMMENT,
    IF,
    ELSE,
    LOOP,
    MATCH,
    PATTERN,
    IS,
    FUNC_KEYWORD,
    NONE_KEYWORD,
    REF_KEYWORD,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    SEMICOLON,
    COMMA,
    ASSIGN,
    EQUAL,
    GREATER_THAN,
    LESS_THAN,
    GREATER_OR_EQUAL,
    LESS_OR_EQUAL,
    NEGATION,
    PLUS,
    MINUS,
    ASTERISK,
    DIVISION,
    INT_DIVISION,
    MODULO,
    INTEGER_VALUE,
    FLOAT_VALUE,
    STRING_LITERAL,
    INT_KEYWORD,
    FLOAT_KEYWORD,
    STRING_KEYWORD,
    DOT,
    IDENTIFIER,
    RETURN
};


#endif //CODE_TOKENTYPE_H
