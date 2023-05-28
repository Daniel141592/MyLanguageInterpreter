#ifndef CODE_VARIABLE_H
#define CODE_VARIABLE_H


#include <string>
#include <variant>
#include <utility>
#include "../parser/structure/ConstantType.h"

class Variable {
    std::string name;
    ConstantType type;
    std::variant<double, int, std::string> value;
    bool mut;
public:
    Variable(std::string n, double v, bool m);
    Variable(std::string n, int v, bool m);
    Variable(std::string n, std::string v, bool m);

    const std::variant<double, int, std::string> &getValue() const;
    void setValue(const std::variant<double, int, std::string> &value);
};


#endif //CODE_VARIABLE_H
