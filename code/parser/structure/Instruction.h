#ifndef CODE_INSTRUCTION_H
#define CODE_INSTRUCTION_H


#include <memory>
#include "../Visitable.h"
#include "../Visitor.h"

class Instruction : public Visitable {
public:
    typedef std::unique_ptr<Instruction> InstructionPtr;
    ~Instruction() override = default;

    void accept(const Visitor* visitor) const override = 0;
};


#endif //CODE_INSTRUCTION_H
