#include "Argument.h"

Argument::Argument(Position p, std::string name, bool r) : identifier(p, std::move(name)), ref(r) {

}

void Argument::accept(Visitor& visitor) const {
    visitor.visit(*this);
}

const Identifier &Argument::getIdentifier() const {
    return identifier;
}

bool Argument::isRef() const {
    return ref;
}
