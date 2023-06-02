#ifndef CODE_ADDITIVEVISITOR_H
#define CODE_ADDITIVEVISITOR_H

#include "Value.h"
#include "../structure/AdditiveType.h"
#include "../ErrorType.h"

#include <functional>

class AdditiveVisitor {
    Value &result;
    AdditiveType type;
public:
    AdditiveVisitor(Value &v, AdditiveType at);

    template<typename T>
    void operator()(T a, T b) {
        switch (type) {
            case AdditiveType::ADD:
                result.setValue(a + b);
                break;
            case AdditiveType::SUBTRACT:
                result.setValue(a - b);
                break;
        }
    }

    void operator()(const std::string &a, const std::string &b) {
        switch (type) {
            case AdditiveType::ADD:
                result.setValue(a + b);
                break;
            case AdditiveType::SUBTRACT:
                throw InvalidOperandsException(VariableType::STRING, VariableType::STRING);
        }
    }

    void operator()(const SimplePair &a, const SimplePair &b) {
        throw InvalidOperandsException(VariableType::STRING, VariableType::STRING);
    }

    template<typename T, typename U>
    void operator()(T& a, U& b) {
        throw InvalidOperandsException(a, b);
    }
};


#endif //CODE_ADDITIVEVISITOR_H
