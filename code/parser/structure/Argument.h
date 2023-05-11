#ifndef CODE_ARGUMENT_H
#define CODE_ARGUMENT_H


#include "../Visitable.h"
#include "Identifier.h"

class Argument : Visitable {
    Identifier identifier;
    bool ref;
public:
    explicit Argument(std::string name, bool r = false);
    ~Argument() override = default;

    void accept(const Visitor* visitor) const override;

    const Identifier &getIdentifier() const;
    bool isRef() const;
};


#endif //CODE_ARGUMENT_H
