#include "IncompletePairVisitor.h"

IncompletePairVisitor::IncompletePairVisitor(std::optional<SimpleType>& opt) : result(opt) {}

void IncompletePairVisitor::operator()(const SimplePair&) {
    throw InvalidUnaryOperandException(VariableType::PAIR);
}

void IncompletePairVisitor::operator()(VariableType) {
    throw EmptyValueException();
}