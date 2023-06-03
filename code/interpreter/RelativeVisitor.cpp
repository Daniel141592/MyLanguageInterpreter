#include "RelativeVisitor.h"

RelativeVisitor::RelativeVisitor(Value& r, RelativeType t) : result(r), type(t) {}

void RelativeVisitor::operator()(const SimplePair& f, const SimplePair& s) {
    Value value;
    if (s.first) {
        std::visit(RelativeVisitor(value, type), f.first.value(), s.first.value());
        if (std::get<int>(value.getValue()) == 0) {
            result.setValue(false);
            return;
        }
    }
    if (s.second) {
        std::visit(RelativeVisitor(value, type), f.second.value(), s.second.value());
        result.setValue(std::get<int>(value.getValue()) != 0);
        return;
    }
    result.setValue(true);
}
