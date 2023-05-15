#include "Block.h"

using InstructionPtr = Instruction::InstructionPtr;

Block::Block(std::vector<InstructionPtr> ins) : instructions(std::move(ins)) {

}


const std::vector<Instruction::InstructionPtr> &Block::getInstructions() const {
    return instructions;
}

void Block::accept(Visitor* visitor) const {
    visitor->visit(std::move(this));
}
