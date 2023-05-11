#include "Identifier.h"

#include <utility>

Identifier::Identifier(std::string n) : name(std::move(n)) {

}

std::string Identifier::getName() const {
    return name;
}

void Identifier::accept(const Visitor* visitor) const {
    visitor->visit(this);
}
