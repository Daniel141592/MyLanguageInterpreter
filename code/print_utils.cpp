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
            {ErrorType::MISSING_PARENTHESIS,         "MISSING_PARENTHESIS"},
            {ErrorType::MISSING_SEMICOLON,           "MISSING_SEMICOLON"},
            {ErrorType::MUT_OUTSIDE_DECLARATION,     "MUT_OUTSIDE_DECLARATION"},
            {ErrorType::EXPRESSION_EXPECTED,         "EXPRESSION_EXPECTED"},
            {ErrorType::IDENTIFIER_EXPECTED,         "IDENTIFIER_EXPECTED"},
            {ErrorType::FUNCTION_REDEFINITION,       "FUNCTION_REDEFINITION"},
            {ErrorType::ARGUMENTS_LIST_EXPECTED,     "ARGUMENTS_LIST_EXPECTED"},
            {ErrorType::BLOCK_EXPECTED,              "BLOCK_EXPECTED"},
            {ErrorType::BRACKET_EXPECTED,            "BRACKET_EXPECTED"},
            {ErrorType::ASSIGN_OR_FUNCTION_CALL_EXPECTED, "ASSIGN_OR_FUNCTION_CALL_EXPECTED"},
            {ErrorType::INVALID_MATCH_SYNTAX,        "INVALID_MATCH_SYNTAX"},
            {ErrorType::FIRST_OR_SECOND_EXPECTED,    "FIRST_OR_SECOND_EXPECTED"},
            {ErrorType::OtherError,                  "OtherError"}
    };
    auto it = errorTypesNames.find(errorType);
    if (it != errorTypesNames.end())
        return it->second;
    return "UnknownErrorType";
}

std::string_view PrintUtils::toString(TokenType tokenType) {
    static const std::unordered_map<TokenType, std::string_view> tokenTypeStringMap {
            { TokenType::END_OF_TEXT,       "END_OF_TEXT" },
            { TokenType::MUT_KEYWORD,       "MUT_KEYWORD" },
            { TokenType::COMMENT,           "COMMENT" },
            { TokenType::IF_KEYWORD,        "IF_KEYWORD" },
            { TokenType::ELSE_KEYWORD,      "ELSE_KEYWORD" },
            { TokenType::LOOP_KEYWORD,      "LOOP_KEYWORD" },
            { TokenType::MATCH_KEYWORD,     "MATCH_KEYWORD" },
            { TokenType::PATTERN_KEYWORD,   "PATTERN_KEYWORD" },
            { TokenType::IS_KEYWORD,        "IS_KEYWORD" },
            { TokenType::FUNC_KEYWORD,      "FUNC_KEYWORD" },
            { TokenType::NONE_KEYWORD,      "NONE_KEYWORD" },
            { TokenType::REF_KEYWORD,       "REF_KEYWORD" },
            { TokenType::LEFT_BRACKET,      "LEFT_BRACKET" },
            { TokenType::RIGHT_BRACKET,     "RIGHT_BRACKET" },
            { TokenType::LEFT_PARENTHESIS,  "LEFT_PARENTHESIS" },
            { TokenType::RIGHT_PARENTHESIS, "RIGHT_PARENTHESIS" },
            { TokenType::SEMICOLON,         "SEMICOLON" },
            { TokenType::COMMA,             "COMMA" },
            { TokenType::ASSIGN,            "ASSIGN" },
            { TokenType::EQUAL,             "EQUAL" },
            { TokenType::NOT_EQUAL,         "NOT_EQUAL" },
            { TokenType::GREATER_THAN,      "GREATER_THAN" },
            { TokenType::LESS_THAN,         "LESS_THAN" },
            { TokenType::GREATER_OR_EQUAL,  "GREATER_OR_EQUAL" },
            { TokenType::LESS_OR_EQUAL,     "LESS_OR_EQUAL" },
            { TokenType::NEGATION,          "NEGATION" },
            { TokenType::PLUS,              "PLUS" },
            { TokenType::MINUS,             "MINUS" },
            { TokenType::ASTERISK,          "ASTERISK" },
            { TokenType::DIVISION,          "DIVISION" },
            { TokenType::INT_DIVISION,      "INT_DIVISION" },
            { TokenType::MODULO,            "MODULO" },
            { TokenType::INTEGER_VALUE,     "INTEGER_VALUE" },
            { TokenType::FLOAT_VALUE,       "FLOAT_VALUE" },
            { TokenType::STRING_LITERAL,    "STRING_LITERAL" },
            { TokenType::INT_KEYWORD,       "INT_KEYWORD" },
            { TokenType::FLOAT_KEYWORD,     "FLOAT_KEYWORD" },
            { TokenType::STRING_KEYWORD,    "STRING_KEYWORD" },
            { TokenType::DOT,               "DOT" },
            { TokenType::IDENTIFIER,        "IDENTIFIER" },
            { TokenType::RETURN_KEYWORD,    "RETURN_KEYWORD" }
    };
    auto it = tokenTypeStringMap.find(tokenType);
    return it == tokenTypeStringMap.end() ? "unknown token" : it->second;
}
