#include "Value.h"

Value::Value() : returned(false) {}

Value::Value(Position p, int v) : position(p), value(v), type(ConstantType::INTEGER), returned(false) {

}

Value::Value(Position p, double v) : position(p), value(v), type(ConstantType::FLOAT), returned(false) {

}

Value::Value(Position p, const std::string& v) : position(p), value(v), type(ConstantType::STRING), returned(false) {

}

const std::optional<std::variant<int, double, std::string>> &Value::getValue() const {
    return value;
}

ConstantType Value::getType() const {
    return type;
}

const Position &Value::getPosition() const {
    return position;
}

void Value::setValue(const std::optional<std::variant<int, double, std::string>> &value) {
    Value::value = value;
}

bool Value::isReturned() const {
    return returned;
}

void Value::setReturned(bool r) {
    Value::returned = r;
}
