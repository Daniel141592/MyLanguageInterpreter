#ifndef CODE_ERRORTYPE_H
#define CODE_ERRORTYPE_H


enum class ErrorType {
    IntRangeError, IncorrectFloatValue, UnknownToken, UnexpectedEndOfText, UnknownEscapeCharacter,
    TooLongStringLiteral, TooLongIdentifier, TooLongComment, InconsistentNewlineSequence, OtherError
};


#endif //CODE_ERRORTYPE_H
