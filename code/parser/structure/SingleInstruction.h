#ifndef CODE_SINGLEINSTRUCTION_H
#define CODE_SINGLEINSTRUCTION_H


#include "Instruction.h"

class SingleInstruction : public Instruction {
public:
    using SingleInstructionPtr = std::unique_ptr<SingleInstruction>;
    ~SingleInstruction() override = default;

    void accept(Visitor* visitor) const override = 0;
};


#endif //CODE_SINGLEINSTRUCTION_H
