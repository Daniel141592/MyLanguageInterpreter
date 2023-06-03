#include "Variable.h"

Variable::Variable() : mut(true) {

}

Variable::Variable(double v, bool m) : type(VariableType::FLOAT), value(v), mut(m) {

}

Variable::Variable(int v, bool m) : type(VariableType::INTEGER), value(v), mut(m) {

}

Variable::Variable(std::string v, bool m) : type(VariableType::STRING), value(v), mut(m) {

}

Variable::Variable(const SimplePair& v, bool m) : type(VariableType::PAIR), value(v), mut(m) {

}

const VariableValueTypename &Variable::getValue() const {
    if (value)
        return value.value();
    throw EmptyValueException();
}

std::optional<VariableType> Variable::getType() const {
    return type;
}

bool Variable::isMut() const {
    return mut;
}

void Variable::setValue(int v) {
    value = v;
    type = VariableType::INTEGER;
}

void Variable::setValue(double v) {
    value = v;
    type = VariableType::FLOAT;
}

void Variable::setValue(const std::string& v) {
    value = v;
    type = VariableType::STRING;
}


void Variable::setValue(const SimplePair &v) {
    value = v;
    type = VariableType::PAIR;
}
