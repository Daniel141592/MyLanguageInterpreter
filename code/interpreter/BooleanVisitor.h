#ifndef CODE_BOOLEANVISITOR_H
#define CODE_BOOLEANVISITOR_H

#include "Value.h"

class BooleanVisitor {
    Value& result;
public:
    explicit BooleanVisitor(Value& r);

    template<typename T>
    void operator()(T value) {
        result.setValue(value != 0);
    }
    void operator()(const std::string& value);
    void operator()(VariableType);
    void operator()(const SimplePair& pair);
};

#endif //CODE_BOOLEANVISITOR_H
