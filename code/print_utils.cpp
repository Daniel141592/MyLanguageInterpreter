#include "print_utils.h"

std::string_view PrintUtils::toString(ErrorType errorType) {
    static const std::unordered_map<ErrorType, std::string_view> errorTypesNames = {
            {ErrorType::IntRangeError,               "IntRangeError"},
            {ErrorType::IncorrectFloatValue,         "IncorrectFloatValue"},
            {ErrorType::UnknownToken,                "UnknownToken"},
            {ErrorType::UnexpectedEndOfText,         "UnexpectedEndOfText"},
            {ErrorType::UnknownEscapeCharacter,      "UnknownEscapeCharacter"},
            {ErrorType::TooLongStringLiteral,        "TooLongStringLiteral"},
            {ErrorType::TooLongIdentifier,           "TooLongIdentifier"},
            {ErrorType::TooLongComment,              "TooLongComment"},
            {ErrorType::InconsistentNewlineSequence, "InconsistentNewlineSequence"},
            {ErrorType::OtherError,                  "OtherError"}
    };
    auto it = errorTypesNames.find(errorType);
    if (it != errorTypesNames.end())
        return it->second;
    return "UnknownErrorType";
}

std::string_view PrintUtils::toString(TokenType tokenType) {
    static const std::unordered_map<TokenType, std::string_view> tokenTypeStringMap {
            { END_OF_TEXT, "END_OF_TEXT" },
            { MUT, "MUT" },
            { COMMENT, "COMMENT" },
            { IF, "IF" },
            { ELSE, "ELSE" },
            { LOOP, "LOOP" },
            { MATCH, "MATCH" },
            { PATTERN, "PATTERN" },
            { IS, "IS" },
            { FUNC_KEYWORD, "FUNC" },
            { NONE_KEYWORD, "NONE" },
            { REF_KEYWORD, "REF" },
            { LEFT_BRACKET, "LEFT_BRACKET" },
            { RIGHT_BRACKET, "RIGHT_BRACKET" },
            { LEFT_PARENTHESIS, "LEFT_PARENTHESIS" },
            { RIGHT_PARENTHESIS, "RIGHT_PARENTHESIS" },
            { SEMICOLON, "SEMICOLON" },
            { COMMA, "COMMA" },
            { ASSIGN, "ASSIGN" },
            { EQUAL, "EQUAL" },
            { GREATER_THAN, "GREATER_THAN" },
            { LESS_THAN, "LESS_THAN" },
            { GREATER_OR_EQUAL, "GREATER_OR_EQUAL" },
            { LESS_OR_EQUAL, "LESS_OR_EQUAL" },
            { NEGATION, "NEGATION" },
            { PLUS, "PLUS" },
            { MINUS, "MINUS" },
            { ASTERISK, "ASTERISK" },
            { DIVISION, "DIVISION" },
            { INT_DIVISION, "INT_DIVISION" },
            { MODULO, "MODULO" },
            { INTEGER_VALUE, "INTEGER_VALUE" },
            { FLOAT_VALUE, "FLOAT_VALUE" },
            { STRING_LITERAL, "STRING_LITERAL" },
            { INT_KEYWORD, "INT" },
            { FLOAT_KEYWORD, "FLOAT" },
            { STRING_KEYWORD, "STRING" },
            { DOT, "DOT" },
            { IDENTIFIER, "IDENTIFIER" },
            { RETURN, "RETURN" }
    };
    auto it = tokenTypeStringMap.find(tokenType);
    return it == tokenTypeStringMap.end() ? "unknown token" : it->second;
}
