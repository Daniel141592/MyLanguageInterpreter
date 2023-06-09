#include "PassFunctionArgumentVisitor.h"

PassFunctionArgumentVisitor::PassFunctionArgumentVisitor(Variable& var) : variable(var) {}

void PassFunctionArgumentVisitor::operator()(VariableType) {
    throw EmptyValueException();
}
