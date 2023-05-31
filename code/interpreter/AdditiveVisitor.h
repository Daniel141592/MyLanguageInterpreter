#ifndef CODE_ADDITIVEVISITOR_H
#define CODE_ADDITIVEVISITOR_H

#include "Value.h"
#include "../structure/AdditiveType.h"
#include "../ErrorType.h"

#include <functional>

class AdditiveVisitor {
    Value &result;
    AdditiveType type;
    std::function<void(ErrorType)> errorHandler;
public:
    AdditiveVisitor(Value &v, AdditiveType at, std::function<void(ErrorType)> onError);

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
                errorHandler(ErrorType::INVALID_OPERAND);
        }
    }

    template<typename T, typename U>
    void operator()(T a, U b) {
        errorHandler(ErrorType::INCOMPATIBLE_DATA_TYPES);
    }
};


#endif //CODE_ADDITIVEVISITOR_H
