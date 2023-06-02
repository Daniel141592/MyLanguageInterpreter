#ifndef CODE_VALUE_H
#define CODE_VALUE_H

#include <variant>
#include <string>
#include <optional>
#include "../structure/ConstantType.h"
#include "../Position.h"
#include "Exceptions.h"
#include "Aliases.h"

class Value {
private:
    std::optional<ValueType> value{};
    Position position;
    bool returned;
public:
    Value();
    Value(const Value& other);
    Value(Position p, int v);
    Value(Position p, double v);
    Value(Position p, const std::string& v);
    Value(Position p, const SimplePair& v);
    Value(Position p, VariableType v);

    const ValueType & getValue() const;
    void setValue(const std::optional<ValueType> &value);
    void setValue(const std::optional<ValueType> &value, Position pos);
    const Position &getPosition() const;
    bool isReturned() const;
    void setReturned(bool returned = true);
    void setPosition(const Position &position);
    Value& operator=(const Value& other);
};


#endif //CODE_VALUE_H
