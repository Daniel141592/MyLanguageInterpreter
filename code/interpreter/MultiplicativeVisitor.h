#ifndef CODE_MULTIPLICATIVEVISITOR_H
#define CODE_MULTIPLICATIVEVISITOR_H

#include "Value.h"
#include "../structure/MultiplicativeType.h"
#include "../ErrorType.h"

#include <functional>

class MultiplicativeVisitor {
    Value &result;
    MultiplicativeType type;
    std::function<void(ErrorType)> errorHandler;
public:
    MultiplicativeVisitor(Value &v, MultiplicativeType at, std::function<void(ErrorType)> onError);

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
            errorHandler(ErrorType::INVALID_OPERAND);
    }

    void operator()(const std::string &a, const std::string &b) const {
        errorHandler(ErrorType::INVALID_OPERAND);
    }

    template<typename T, typename U>
    void operator()(T a, U b) {
        errorHandler(ErrorType::INCOMPATIBLE_DATA_TYPES);
    }

private:
    template<typename T>
    void exec(T a, T b) {
        switch (type) {
            case MultiplicativeType::MULTIPLY:
                result.setValue(a * b);
                break;
            case MultiplicativeType::DIVIDE:
                result.setValue(a / b);
                break;
            case MultiplicativeType::INT_DIVIDE:
                result.setValue((int) a / (int) b);
                break;
            default:
                break;
        }
    }
};


#endif //CODE_MULTIPLICATIVEVISITOR_H
