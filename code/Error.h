#ifndef CODE_ERROR_H
#define CODE_ERROR_H


#include <string>

#include "ErrorType.h"
#include "Position.h"

class Error {
    ErrorType type;
    Position position;
    std::string msg;
public:
    Error(ErrorType, Position);
    Error(ErrorType, Position, std::string);

    ErrorType getType() const;

    const Position &getPosition() const;

    const std::string &getMsg() const;

};


#endif //CODE_ERROR_H
