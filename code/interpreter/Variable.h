#ifndef CODE_VARIABLE_H
#define CODE_VARIABLE_H


#include <string>
#include <variant>
#include <utility>
#include "../structure/ConstantType.h"

class Variable {
    ConstantType type;
    std::variant<double, int, std::string> value;
    bool mut;
public:
    Variable(double v, bool m);
    Variable(int v, bool m);
    Variable(std::string v, bool m);

    const std::variant<double, int, std::string> &getValue() const;
    void setValue(const std::variant<double, int, std::string> &value);
};


#endif //CODE_VARIABLE_H
