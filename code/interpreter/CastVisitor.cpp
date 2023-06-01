#include "CastVisitor.h"

CastVisitor::CastVisitor(ConstantType t, Value& r) : to(t), result(r) {};

void CastVisitor::operator()(double from) {
    if (to == ConstantType::INTEGER)
        result.setValue((int)from);
    else if (to == ConstantType::STRING)
        convertToString(from);
}

void CastVisitor::operator()(int from) {
    if (to == ConstantType::FLOAT)
        result.setValue((double)from);
    else if (to == ConstantType::STRING)
        convertToString(from);
}

void CastVisitor::operator()(const std::string& from) {
    if (to == ConstantType::INTEGER)
        convertFromString<int>(from);
    else if (to == ConstantType::FLOAT)
        convertFromString<double>(from);
}
