#include "AdditiveVisitor.h"

AdditiveVisitor::AdditiveVisitor(Value &v, AdditiveType at) : type(at), result(v) {};

void AdditiveVisitor::operator()(const std::string &a, const std::string &b) {
    switch (type) {
        case AdditiveType::ADD:
            result.setValue(a + b);
            break;
        case AdditiveType::SUBTRACT:
            throw InvalidOperandsException(VariableType::STRING, VariableType::STRING);
    }
}

void AdditiveVisitor::operator()(const SimplePair &a, const SimplePair &b) {
    throw InvalidOperandsException(VariableType::STRING, VariableType::STRING);
}

void AdditiveVisitor::operator()(VariableType, VariableType) {
    throw EmptyValueException();
}
