#include "RelativeVisitor.h"

RelativeVisitor::RelativeVisitor(Value& r, RelativeType t) : result(r), type(t) {}

void RelativeVisitor::operator()(const SimplePair& f, const SimplePair& s) {
    Value value;
    std::visit(RelativeVisitor(value, type), f.first, s.first);
    if (std::get<int>(value.getValue()) == 0)
        result.setValue(false);
    else {
        std::visit(RelativeVisitor(value, type), f.second, s.second);
        result.setValue(std::get<int>(value.getValue()) != 0);
    }
}
