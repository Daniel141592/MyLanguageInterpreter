#ifndef CODE_ERRORTYPE_H
#define CODE_ERRORTYPE_H


enum class ErrorType {
    IntRangeError, IncorrectFloatValue, UnknownToken, UnexpectedEndOfText, UnknownEscapeCharacter,
    TooLongStringLiteral, TooLongIdentifier, TooLongComment, InconsistentNewlineSequence, MISSING_PARENTHESIS,
    MISSING_SEMICOLON, MUT_OUTSIDE_DECLARATION, EXPRESSION_EXPECTED, IDENTIFIER_EXPECTED, FUNCTION_REDEFINITION,
    ARGUMENTS_LIST_EXPECTED, BLOCK_EXPECTED,

    OtherError
};


#endif //CODE_ERRORTYPE_H
