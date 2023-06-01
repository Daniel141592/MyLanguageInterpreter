#include "BooleanVisitor.h"

BooleanVisitor::BooleanVisitor(Value& r) : result(r) {};

BooleanVisitor::BooleanVisitor(Value &r, Position pos) : result(r), position(pos) {}
