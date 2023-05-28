#ifndef CODE_MYLANGINTERPRETER_H
#define CODE_MYLANGINTERPRETER_H

#include <functional>

#include "Interpreter.h"
#include "../Visitor.h"
#include "../parser/structure/Program.h"
#include "../Position.h"
#include "../ErrorType.h"

class MyLangInterpreter : public Interpreter, public Visitor {
public:
    using HandlerType = std::function<void(Position, ErrorType)>;
private:
    const Program program;
    std::ostream& os;
    std::istream& is;
    HandlerType errorHandler;
public:
    MyLangInterpreter(Program  p, std::ostream& o, std::istream& i, HandlerType& onError);
    ~MyLangInterpreter() override = default;
};

#endif //CODE_MYLANGINTERPRETER_H
