#ifndef CODE_INSTRUCTION_H
#define CODE_INSTRUCTION_H


#include <memory>
#include "../parser/Visitable.h"
#include "../Visitor.h"

class Instruction : public Visitable {
public:
    typedef std::unique_ptr<Instruction> InstructionPtr;
    ~Instruction() override = default;

    void accept(Visitor& visitor) const override = 0;
};


#endif //CODE_INSTRUCTION_H
