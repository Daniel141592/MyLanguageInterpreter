#include "Pair.h"

Pair::Pair(Pair::ExpressionPtr f, Pair::ExpressionPtr s) : Expression(f->getPosition()), first(std::move(f)), second(std::move(s)) {

}

const Pair::ExpressionPtr &Pair::getFirst() const {
    return first;
}

const Pair::ExpressionPtr &Pair::getSecond() const {
    return second;
}

void Pair::accept(Visitor& visitor) const {
    visitor.visit(*this);
}
