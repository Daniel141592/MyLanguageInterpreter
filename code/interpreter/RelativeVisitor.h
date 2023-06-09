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
        if (type != RelativeType::IS)
            throw InvalidOperandsException(first, second);
        result.setValue(0);
    }

    void operator()(const SimplePair& f, const SimplePair& s);

    VariableType variableType(int) {
        return VariableType::INTEGER;
    }

    VariableType variableType(double) {
        return VariableType::FLOAT;
    }

    VariableType variableType(const std::string &) {
        return VariableType::STRING;
    }

    VariableType variableType(const SimplePair&) {
        return VariableType::PAIR;
    }

    VariableType variableType(VariableType) {
        return VariableType::NONE;
    }

    template<typename T>
    void operator()(const T& f, VariableType s) {
        if (type == RelativeType::IS)
            result.setValue(variableType(f) == s);
        else
            throw InvalidOperandsException(f, s);
    }

    void operator()(VariableType, VariableType) {
        throw EmptyValueException();
    }
};


#endif //CODE_RELATIVEVISITOR_H
