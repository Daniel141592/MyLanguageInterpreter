#include "Value.h"

Value::Value() : returned(false) {}

Value::Value(Position p) : position(p), returned(false) {

}

Value::Value(Position p, int v) : position(p), value(v), returned(false) {

}

Value::Value(Position p, double v) : position(p), value(v), returned(false) {

}

Value::Value(Position p, const std::string& v) : position(p), value(v), returned(false) {

}

Value::Value(Position p, const SimplePair &v) : position(p), value(v), returned(false) {

}

Value::Value(Position p, VariableType v) : position(p), value(v), returned(false) {

}

Value::Value(const Value &other) = default;

const ValueType & Value::getValue() const {
    if (value)
        return value.value();
    throw EmptyValueException();
}

const Position &Value::getPosition() const {
    return position;
}

void Value::setValue(const std::optional<ValueType> &value) {
    Value::value = value;
}

void Value::setValue(const std::optional<ValueType> &value, Position pos) {
    setValue(value);
    position = pos;
}

bool Value::isReturned() const {
    return returned;
}

void Value::setReturned(bool r) {
    Value::returned = r;
}

void Value::setPosition(const Position &pos) {
    position = pos;
}

const std::optional<ValueType> Value::getOptionalValue() const {
    return value;
}

Value &Value::operator=(const Value &other) = default;

