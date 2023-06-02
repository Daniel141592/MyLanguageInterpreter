#ifndef CODE_PAIRVISITOR_H
#define CODE_PAIRVISITOR_H


#include "Value.h"

class PairVisitor {
    Value& value;
public:
    explicit PairVisitor(Value& v);
    template<typename T, typename U>
    void operator()(const T& f, const U& s) {
        SimplePair simplePair(f, s);
        value.setValue(simplePair);
    }

    void operator()(const SimplePair& f, const SimplePair& s);
    void operator()(VariableType, VariableType);

    template<typename T>
    void operator()(VariableType, const T&) {
        throw EmptyValueException();
    }

    template<typename T>
    void operator()(const T&, VariableType) {
        throw EmptyValueException();
    }

    template<typename T>
    void operator()(const SimplePair& f, const T& s) {
        throw IncompatibleTypeException(s, f);
    }

    template<typename T>
    void operator()(const T& f, const SimplePair& s) {
        throw IncompatibleTypeException(f, s);
    }

    void operator()(VariableType, const SimplePair&);
    void operator()(const SimplePair&, VariableType);
};

#endif //CODE_PAIRVISITOR_H
