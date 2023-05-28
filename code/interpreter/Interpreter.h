#ifndef CODE_INTERPRETER_H
#define CODE_INTERPRETER_H

#include "../structure/Program.h"
#include "../Position.h"
#include "../ErrorType.h"

class Interpreter {
public:
    typedef std::function<void(Position, ErrorType)> HandlerType;
    ~Interpreter() = default;
    virtual void execute(const Program& program) = 0;
};

#endif //CODE_INTERPRETER_H
