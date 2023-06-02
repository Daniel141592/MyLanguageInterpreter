#include "MultiplicativeVisitor.h"

MultiplicativeVisitor::MultiplicativeVisitor(Value &v, MultiplicativeType at)
        : type(at), result(v) {};

void MultiplicativeVisitor::operator()(int a, int b) {
    if (type == MultiplicativeType::MODULO)
        result.setValue(a % b);
    else
        exec(a, b);
}

void MultiplicativeVisitor::operator()(double a, double b) {
    if (type != MultiplicativeType::MODULO)
        exec(a, b);
    else
        throw InvalidOperandsException(a, b);
}

void MultiplicativeVisitor::operator()(const std::string &a, const std::string &b) const {
    throw InvalidOperandsException(a, b);
}

void MultiplicativeVisitor::operator()(const SimplePair& a, const SimplePair& b) const {
    throw InvalidOperandsException(a, b);
}

void MultiplicativeVisitor::operator()(VariableType) {
    throw EmptyValueException();
}