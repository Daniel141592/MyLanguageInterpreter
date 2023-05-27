#ifndef CODE_TYPENAME_H
#define CODE_TYPENAME_H


#include "Factor.h"
#include "ConstantType.h"

class Typename : public Factor {
    ConstantType type;
public:
    Typename(Position p, ConstantType constantType);
    ConstantType getType() const;

    void accept(Visitor *visitor) const override;
};


#endif //CODE_TYPENAME_H
