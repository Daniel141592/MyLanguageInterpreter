#ifndef CODE_DECLARATION_H
#define CODE_DECLARATION_H

#include "SingleInstruction.h"

class Declaration : public SingleInstruction {
public:
    ~Declaration() override = default;
    void accept(const Visitor *visitor) const override = 0;
};


#endif //CODE_DECLARATION_H
