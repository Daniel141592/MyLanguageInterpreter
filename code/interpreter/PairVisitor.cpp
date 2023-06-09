#include "PairVisitor.h"

PairVisitor::PairVisitor(Value& v) : value(v) {}

void PairVisitor::operator()(const SimplePair& f, const SimplePair& s) {
    throw IncompatibleTypeException(s, f);
}

void PairVisitor::operator()(VariableType, VariableType) {
    throw EmptyValueException();
}

void PairVisitor::operator()(VariableType, const SimplePair &) {
    throw EmptyValueException();
}

void PairVisitor::operator()(const SimplePair &, VariableType) {
    throw EmptyValueException();
}
