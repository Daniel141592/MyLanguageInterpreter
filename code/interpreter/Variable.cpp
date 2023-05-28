#include "Variable.h"

Variable::Variable(double v, bool m) : type(ConstantType::FLOAT), value(v), mut(m) {

}

Variable::Variable(int v, bool m) : type(ConstantType::INTEGER), value(v), mut(m) {

}

Variable::Variable(std::string v, bool m) : type(ConstantType::STRING), value(v), mut(m) {

}

const std::variant<double, int, std::string> &Variable::getValue() const {
    return value;
}

void Variable::setValue(const std::variant<double, int, std::string> &value) {
    Variable::value = value;
}
