#include "Variable.h"

Variable::Variable(std::string n, double v, bool m) : name(std::move(n)), type(ConstantType::FLOAT), value(v), mut(m) {

}

Variable::Variable(std::string n, int v, bool m) : name(std::move(n)), type(ConstantType::INTEGER), value(v), mut(m) {

}

Variable::Variable(std::string n, std::string v, bool m) : name(std::move(n)), type(ConstantType::STRING), value(v), mut(m) {

}

const std::variant<double, int, std::string> &Variable::getValue() const {
    return value;
}

void Variable::setValue(const std::variant<double, int, std::string> &value) {
    Variable::value = value;
}
