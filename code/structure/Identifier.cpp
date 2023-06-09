#include "Identifier.h"

#include <utility>

Identifier::Identifier(Position p, std::string n) : Factor(p), name(std::move(n)) {

}

std::string Identifier::getName() const {
    return name;
}

void Identifier::accept(Visitor& visitor) const {
    visitor.visit(*this);
}
