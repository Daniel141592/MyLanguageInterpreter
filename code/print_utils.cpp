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
            { TokenType::END_OF_TEXT, "END_OF_TEXT" },
            { TokenType::MUT, "MUT" },
            { TokenType::COMMENT, "COMMENT" },
            { TokenType::IF, "IF" },
            { TokenType::ELSE, "ELSE" },
            { TokenType::LOOP, "LOOP" },
            { TokenType::MATCH, "MATCH" },
            { TokenType::PATTERN, "PATTERN" },
            { TokenType::IS, "IS" },
            { TokenType::FUNC_KEYWORD, "FUNC" },
            { TokenType::NONE_KEYWORD, "NONE" },
            { TokenType::REF_KEYWORD, "REF" },
            { TokenType::LEFT_BRACKET, "LEFT_BRACKET" },
            { TokenType::RIGHT_BRACKET, "RIGHT_BRACKET" },
            { TokenType::LEFT_PARENTHESIS, "LEFT_PARENTHESIS" },
            { TokenType::RIGHT_PARENTHESIS, "RIGHT_PARENTHESIS" },
            { TokenType::SEMICOLON, "SEMICOLON" },
            { TokenType::COMMA, "COMMA" },
            { TokenType::ASSIGN, "ASSIGN" },
            { TokenType::EQUAL, "EQUAL" },
            { TokenType::NOT_EQUAL, "NOT_EQUAL" },
            { TokenType::GREATER_THAN, "GREATER_THAN" },
            { TokenType::LESS_THAN, "LESS_THAN" },
            { TokenType::GREATER_OR_EQUAL, "GREATER_OR_EQUAL" },
            { TokenType::LESS_OR_EQUAL, "LESS_OR_EQUAL" },
            { TokenType::NEGATION, "NEGATION" },
            { TokenType::PLUS, "PLUS" },
            { TokenType::MINUS, "MINUS" },
            { TokenType::ASTERISK, "ASTERISK" },
            { TokenType::DIVISION, "DIVISION" },
            { TokenType::INT_DIVISION, "INT_DIVISION" },
            { TokenType::MODULO, "MODULO" },
            { TokenType::INTEGER_VALUE, "INTEGER_VALUE" },
            { TokenType::FLOAT_VALUE, "FLOAT_VALUE" },
            { TokenType::STRING_LITERAL, "STRING_LITERAL" },
            { TokenType::INT_KEYWORD, "INT" },
            { TokenType::FLOAT_KEYWORD, "FLOAT" },
            { TokenType::STRING_KEYWORD, "STRING" },
            { TokenType::DOT, "DOT" },
            { TokenType::IDENTIFIER, "IDENTIFIER" },
            { TokenType::RETURN, "RETURN" }
    };
    auto it = tokenTypeStringMap.find(tokenType);
    return it == tokenTypeStringMap.end() ? "unknown token" : it->second;
}
