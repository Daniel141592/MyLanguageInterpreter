#ifndef CODE_BOOLEANVISITOR_H
#define CODE_BOOLEANVISITOR_H

#include "Value.h"

class BooleanVisitor {
    Value& result;
    Position position;
public:
    explicit BooleanVisitor(Value& r);
    BooleanVisitor(Value& r, Position pos);

    template<typename T>
    void operator()(T value) {
        result.setValue(value != 0, position);
    }
    void operator()(const std::string& value) {
        result.setValue(!value.empty(), position);
    }
};

#endif //CODE_BOOLEANVISITOR_H
