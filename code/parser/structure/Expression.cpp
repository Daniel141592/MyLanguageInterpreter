#include "Expression.h"

Expression::Expression(Position p) : position(p) {}

const Position &Expression::getPosition() const {
    return position;
}
