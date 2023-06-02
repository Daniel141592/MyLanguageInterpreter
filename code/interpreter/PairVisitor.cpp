#include "PairVisitor.h"

PairVisitor::PairVisitor(Value& v) : value(v) {}

void PairVisitor::operator()(const SimplePair& f, const SimplePair& s) {
    throw IncompatibleTypeException(s, f);
}