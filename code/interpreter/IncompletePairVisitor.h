#ifndef CODE_INCOMPLETEPAIRVISITOR_H
#define CODE_INCOMPLETEPAIRVISITOR_H

#include "Aliases.h"
#include "Exceptions.h"

class IncompletePairVisitor {
    std::optional<SimpleType>& result;
public:
    explicit IncompletePairVisitor(std::optional<SimpleType>& opt);
    void operator()(const SimplePair&);
    void operator()(VariableType);

    template<typename T>
    void operator()(const T& value) {
        result = value;
    }
};


#endif //CODE_INCOMPLETEPAIRVISITOR_H
