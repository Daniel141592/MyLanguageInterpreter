#ifndef CODE_STATEMENT_H
#define CODE_STATEMENT_H

#include "Instruction.h"

class Statement : public Instruction {
public:
    ~Statement() override = default;

    void accept(const Visitor* visitor) const override = 0;
};

#endif //CODE_STATEMENT_H
