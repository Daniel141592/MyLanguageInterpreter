#include "BooleanVisitor.h"

BooleanVisitor::BooleanVisitor(Value& r) : result(r) {}

void BooleanVisitor::operator()(const std::string& value) {
    result.setValue(!value.empty());
}

void BooleanVisitor::operator()(VariableType) {
    throw EmptyValueException();
}

void BooleanVisitor::operator()(const SimplePair& pair) {
    Value v;
    std::visit(BooleanVisitor(v), pair.first);
    if (std::get<int>(v.getValue()) != 0)
        result.setValue(true);
    else {
        std::visit(BooleanVisitor(v), pair.second);
        result.setValue(std::get<int>(v.getValue()) != 0);
    }
}