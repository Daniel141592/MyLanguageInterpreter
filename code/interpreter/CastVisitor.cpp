#include "CastVisitor.h"

CastVisitor::CastVisitor(VariableType t, Value& r) : to(t), result(r) {};

CastVisitor::CastVisitor(ConstantType t, Value &r): result(r) {
    if (t == ConstantType::INTEGER)
        to = VariableType::INTEGER;
    else if (t == ConstantType::FLOAT)
        to = VariableType::FLOAT;
    else if (t == ConstantType::STRING)
        to = VariableType::STRING;
}

void CastVisitor::operator()(double from) {
    if (to == VariableType::INTEGER)
        result.setValue((int)from);
    else if (to == VariableType::STRING)
        convertToString(from);
    else if (to == VariableType::PAIR)
        throw InvalidConversionException(VariableType::FLOAT, VariableType::PAIR);
}

void CastVisitor::operator()(int from) {
    if (to == VariableType::FLOAT)
        result.setValue((double)from);
    else if (to == VariableType::STRING)
        convertToString(from);
    else if (to == VariableType::PAIR)
        throw InvalidConversionException(VariableType::FLOAT, VariableType::PAIR);
}

void CastVisitor::operator()(const std::string& from) {
    if (to == VariableType::INTEGER)
        convertFromString<int>(from);
    else if (to == VariableType::FLOAT)
        convertFromString<double>(from);
    else if (to == VariableType::PAIR)
        throw InvalidConversionException(VariableType::FLOAT, VariableType::PAIR);
}

void CastVisitor::operator()(const SimplePair& from) {
    if (to == VariableType::INTEGER)
        throw InvalidConversionException(VariableType::PAIR, VariableType::INTEGER);
    else if (to == VariableType::FLOAT)
        throw InvalidConversionException(VariableType::PAIR, VariableType::FLOAT);
    else if (to == VariableType::STRING)
        convertToString(from);
}
