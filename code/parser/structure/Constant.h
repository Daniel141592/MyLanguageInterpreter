#ifndef CODE_CONSTANT_H
#define CODE_CONSTANT_H

#include <variant>
#include <string>

#include "Factor.h"
#include "ConstantType.h"

class Constant : public Factor {
    std::variant<int, double, std::string> value;
    ConstantType constantType;
public:
    Constant(Position p, int v);
    Constant(Position p, double v);
    Constant(Position p, std::string v);
    const std::variant<int, double, std::string> &getValue() const;
    ConstantType getConstantType() const;

    void accept(const Visitor *visitor) const override;
};


#endif //CODE_CONSTANT_H
