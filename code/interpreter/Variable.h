#ifndef CODE_VARIABLE_H
#define CODE_VARIABLE_H

#include <string>
#include <variant>
#include <utility>
#include <memory>
#include <optional>

#include "../structure/ConstantType.h"
#include "Exceptions.h"

class Variable {
    std::optional<ConstantType> type;
    std::optional<std::variant<double, int, std::string>> value;
    bool mut;
public:
    using VariablePtr = std::unique_ptr<Variable>;
    Variable();
    Variable(double v, bool m);
    Variable(int v, bool m);
    Variable(std::string v, bool m);
    Variable(const std::variant<double, int, std::string>& v, bool m);

    const std::variant<double, int, std::string> &getValue() const;
    std::optional<ConstantType> getType() const;
    bool isMut() const;
    void setValue(int v);
    void setValue(double v);
    void setValue(const std::string& v);
};


#endif //CODE_VARIABLE_H
