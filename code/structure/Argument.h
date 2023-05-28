#ifndef CODE_ARGUMENT_H
#define CODE_ARGUMENT_H


#include "../parser/Visitable.h"
#include "Identifier.h"

class Argument : Visitable {
    Identifier identifier;
    bool ref;
public:
    Argument(Position p, std::string name, bool r = false);
    ~Argument() override = default;

    void accept(Visitor& visitor) const override;

    const Identifier &getIdentifier() const;
    bool isRef() const;
};


#endif //CODE_ARGUMENT_H
