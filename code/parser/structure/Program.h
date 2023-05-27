#ifndef CODE_PROGRAM_H
#define CODE_PROGRAM_H

#include <vector>
#include <variant>
#include <utility>
#include <memory>

#include "Instruction.h"
#include "../Visitable.h"


class Program : public Visitable {
    using InstructionPtr = Instruction::InstructionPtr;
    std::vector<InstructionPtr> instructions;
public:
    explicit Program(std::vector<InstructionPtr> ins);
    const std::vector<InstructionPtr>& getInstructions() const;

    void accept(Visitor* visitor) const override;
};


#endif //CODE_PROGRAM_H
