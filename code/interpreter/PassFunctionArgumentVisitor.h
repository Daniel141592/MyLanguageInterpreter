#ifndef CODE_PASSFUNCTIONARGUMENTVISITOR_H
#define CODE_PASSFUNCTIONARGUMENTVISITOR_H


#include "Variable.h"

class PassFunctionArgumentVisitor {
    Variable& variable;
public:
    explicit PassFunctionArgumentVisitor(Variable& var);

    template<typename T>
    void operator()(const T& value) {
        variable = Variable(value, true);
    }

    void operator()(VariableType);
};


#endif //CODE_PASSFUNCTIONARGUMENTVISITOR_H
