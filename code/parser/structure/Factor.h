#ifndef CODE_FACTOR_H
#define CODE_FACTOR_H

#include "Expression.h"

class Factor : public Expression {
protected:
    Factor(Position p) : Expression(p) {}
public:
    ~Factor() override = default;

    void accept(const Visitor *visitor) const override = 0;
};


#endif //CODE_FACTOR_H
