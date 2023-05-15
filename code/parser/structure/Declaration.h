#ifndef CODE_DECLARATION_H
#define CODE_DECLARATION_H

#include "SingleInstruction.h"

class Declaration : public SingleInstruction {
public:
    using DeclarationPtr = std::unique_ptr<Declaration>;

    ~Declaration() override = default;
    void accept(Visitor* visitor) const override = 0;
};


#endif //CODE_DECLARATION_H
