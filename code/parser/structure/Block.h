#ifndef CODE_BLOCK_H
#define CODE_BLOCK_H

#include <variant>
#include <vector>

#include "Instruction.h"


class Block : public Instruction {
public:
    using InstructionPtr = Instruction::InstructionPtr;
    using BlockPtr = std::unique_ptr<Block>;
private:
    std::vector<InstructionPtr> instructions;
public:
    explicit Block(std::vector<InstructionPtr> ins);
    const std::vector<InstructionPtr>& getInstructions() const;

    void accept(const Visitor* visitor) const override;
};


#endif //CODE_BLOCK_H
