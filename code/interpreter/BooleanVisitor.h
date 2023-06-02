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

    void operator()(const SimplePair& pair) {
        Value v;
        std::visit(BooleanVisitor(v), pair.first);
        if (std::get<int>(v.getValue()) != 0)
            result.setValue(true);
        else {
            std::visit(BooleanVisitor(v), pair.second);
            result.setValue(std::get<int>(v.getValue()) != 0);
        }
    }
};

#endif //CODE_BOOLEANVISITOR_H
