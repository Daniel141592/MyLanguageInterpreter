#ifndef CODE_RELATIVEVISITOR_H
#define CODE_RELATIVEVISITOR_H


#include "Value.h"
#include "../structure/RelativeType.h"

class RelativeVisitor {
    Value& result;
    RelativeType type;
public:
    RelativeVisitor(Value& r, RelativeType t);

    template<typename T>
    void operator()(const T& first, const T& second) {
        switch (type) {
            case RelativeType::EQUAL:
            case RelativeType::IS:
                result.setValue(first == second);
                break;
            case RelativeType::NOT_EQUAL:
                result.setValue(first != second);
                break;
            case RelativeType::GREATER:
                result.setValue(first > second);
                break;
            case RelativeType::LESS:
                result.setValue(first < second);
                break;
            case RelativeType::GREATER_EQUAL:
                result.setValue(first >= second);
                break;
            case RelativeType::LESS_EQUAL:
                result.setValue(first <= second);
                break;
        }
    }

    template<typename T>
    void operator()(const T& first, const SimplePair& second) {
        if (type != RelativeType::IS)
            throw InvalidOperandsException(first, second);
        result.setValue(0);
    }

    template<typename T, typename U>
    void operator()(const T& first, const U& second) {
        throw InvalidOperandsException(first, second);
    }

    void operator()(const SimplePair& f, const SimplePair& s);
};


#endif //CODE_RELATIVEVISITOR_H
