#ifndef CODE_VALUE_H
#define CODE_VALUE_H

#include <variant>
#include <string>
#include <optional>
#include "../structure/ConstantType.h"
#include "../Position.h"
#include "Exceptions.h"

class Value {
    std::optional<std::variant<int, double, std::string>> value{};
    ConstantType type;
    Position position;
    bool returned;
public:
    Value();
    Value(Position p, int v);
    Value(Position p, double v);
    Value(Position p, const std::string& v);

    const std::variant<int, double, std::string> &getValue() const;
    void setValue(const std::optional<std::variant<int, double, std::string>> &value);
    ConstantType getType() const;
    const Position &getPosition() const;
    bool isReturned() const;
    void setReturned(bool returned = true);
};


#endif //CODE_VALUE_H
