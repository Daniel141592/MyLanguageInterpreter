#include "Variable.h"

Variable::Variable() : mut(true) {

}

Variable::Variable(double v, bool m) : type(ConstantType::FLOAT), value(v), mut(m) {

}

Variable::Variable(int v, bool m) : type(ConstantType::INTEGER), value(v), mut(m) {

}

Variable::Variable(std::string v, bool m) : type(ConstantType::STRING), value(v), mut(m) {

}

const std::variant<double, int, std::string> &Variable::getValue() const {
    if (value)
        return value.value();
    throw EmptyValueException();
}

std::optional<ConstantType> Variable::getType() const {
    return type;
}

bool Variable::isMut() const {
    return mut;
}

void Variable::setValue(int v) {
    value = v;
    type = ConstantType::INTEGER;
}

void Variable::setValue(double v) {
    value = v;
    type = ConstantType::FLOAT;
}

void Variable::setValue(const std::string& v) {
    value = v;
    type = ConstantType::STRING;
}
