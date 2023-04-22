#ifndef CODE_ERRORTYPE_H
#define CODE_ERRORTYPE_H


enum ErrorType {
    IntRangeError, IncorrectFloatValue, UnknownToken, UnexpectedEndOfText, UnknownEscapeCharacter,
    TooLongStringLiteral, TooLongIdentifier, TooLongComment, OtherError
};


#endif //CODE_ERRORTYPE_H
