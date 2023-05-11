#include "Argument.h"

Argument::Argument(std::string name, bool r) : identifier(std::move(name)), ref(r) {

}

void Argument::accept(const Visitor *visitor) const {
    visitor->visit(this);
}

const Identifier &Argument::getIdentifier() const {
    return identifier;
}

bool Argument::isRef() const {
    return ref;
}
