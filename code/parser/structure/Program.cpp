#include "Program.h"

using InstructionPtr = Instruction::InstructionPtr;

Program::Program(std::vector<InstructionPtr> ins) : instructions(std::move(ins)) {

}

void Program::accept(Visitor* visitor) const {
    visitor->visit(std::move(this));
}

const std::vector<InstructionPtr>& Program::getInstructions() const {
    return instructions;
}
