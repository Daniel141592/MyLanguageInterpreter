#include "Error.h"

#include <utility>

Error::Error(ErrorType et, Position pos) : type(et), position(pos) {
    switch (et) {
        case IntRangeError:
            msg = "IntRangeError";
            break;
        case IncorrectFloatValue:
            msg = "IncorrectFloatValue";
            break;
        case UnknownToken:
            msg = "UnknownToken";
            break;
        case UnexpectedEndOfText:
            msg = "UnexpectedEndOfText";
            break;
        case UnknownEscapeCharacter:
            msg = "UnknownEscapeCharacter";
            break;
        case TooLongStringLiteral:
            msg = "TooLongStringLiteral";
            break;
        case OtherError:
            msg = "OtherError";
            break;
    }
}

Error::Error(ErrorType et, Position pos, std::string m) : type(et), position(pos), msg(std::move(m)) {}

ErrorType Error::getType() const {
    return type;
}

const Position &Error::getPosition() const {
    return position;
}

const std::string &Error::getMsg() const {
    return msg;
}
