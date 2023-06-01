#ifndef CODE_MULTIPLICATIVEVISITOR_H
#define CODE_MULTIPLICATIVEVISITOR_H

#include "Value.h"
#include "../structure/MultiplicativeType.h"
#include "../ErrorType.h"
#include "Exceptions.h"

#include <functional>

class MultiplicativeVisitor {
    Value &result;
    MultiplicativeType type;
public:
    MultiplicativeVisitor(Value &v, MultiplicativeType at);

    void operator()(int a, int b) {
        if (type == MultiplicativeType::MODULO)
            result.setValue(a % b);
        else
            exec(a, b);
    }

    void operator()(double a, double b) {
        if (type != MultiplicativeType::MODULO)
            exec(a, b);
        else
            throw InvalidOperands(a, b);
    }

    void operator()(const std::string &a, const std::string &b) const {
        throw InvalidOperands(a, b);
    }

    template<typename T, typename U>
    void operator()(T a, U b) {
        throw InvalidOperands(a, b);
    }

private:
    template<typename T>
    void exec(T a, T b) {
        switch (type) {
            case MultiplicativeType::MULTIPLY:
                result.setValue(a * b);
                break;
            case MultiplicativeType::DIVIDE:
                if (b == 0)
                    throw DivisionByZeroException();
                result.setValue(a / b);
                break;
            case MultiplicativeType::INT_DIVIDE:
                if (b == 0)
                    throw DivisionByZeroException();
                result.setValue((int) a / (int) b);
                break;
            default:
                break;
        }
    }
};


#endif //CODE_MULTIPLICATIVEVISITOR_H
