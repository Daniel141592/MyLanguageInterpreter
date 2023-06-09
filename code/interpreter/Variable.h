#ifndef CODE_VARIABLE_H
#define CODE_VARIABLE_H

#include <string>
#include <variant>
#include <utility>
#include <memory>
#include <optional>

#include "Exceptions.h"
#include "Value.h"
#include "VariableType.h"
#include "Aliases.h"

class Variable {
public:
    std::optional<VariableType> type;
    std::optional<VariableValueTypename> value;
    bool mut;
public:
    using VariablePtr = std::unique_ptr<Variable>;
    Variable();
    Variable(double v, bool m);
    Variable(int v, bool m);
    Variable(std::string v, bool m);
    Variable(const SimplePair& v, bool m);

    const VariableValueTypename &getValue() const;
    std::optional<VariableType> getType() const;
    bool isMut() const;
    void setValue(int v);
    void setValue(double v);
    void setValue(const std::string& v);
    void setValue(const SimplePair& v);
};


#endif //CODE_VARIABLE_H
