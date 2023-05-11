#ifndef CODE_SINGLEINSTRUCTION_H
#define CODE_SINGLEINSTRUCTION_H


#include "Instruction.h"

class SingleInstruction : public Instruction {
public:
    ~SingleInstruction() override = default;

    void accept(const Visitor* visitor) const override = 0;
};


#endif //CODE_SINGLEINSTRUCTION_H
