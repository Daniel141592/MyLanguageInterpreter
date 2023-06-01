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
    void operator()(const std::string& value) {
        result.setValue(!value.empty());
    }
};

#endif //CODE_BOOLEANVISITOR_H
