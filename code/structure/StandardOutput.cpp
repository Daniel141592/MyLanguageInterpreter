#include "StandardOutput.h"

StandardOutput::StandardOutput(std::ostream &o) : os(o) {

}

void StandardOutput::accept(Visitor &visitor) const {
    visitor.visit(*this);
}

void StandardOutput::print(const Value& value) const {
    std::visit([&](const auto& v) {
        os << v;
    }, value.getValue());
}
