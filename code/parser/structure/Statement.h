#ifndef CODE_STATEMENT_H
#define CODE_STATEMENT_H

#include "Instruction.h"

class Statement : public Instruction {
public:
    using StatementPtr = std::unique_ptr<Statement>;
    ~Statement() override = default;

    void accept(Visitor* visitor) const override = 0;
};

#endif //CODE_STATEMENT_H
