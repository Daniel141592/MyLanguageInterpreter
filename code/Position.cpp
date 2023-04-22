#include "Position.h"

Position::Position() : column(1), line(1) {

}

Position::Position(int c, int l) : column(c), line(l) {

}

int Position::getColumn() const {
    return column;
}

void Position::setColumn(int c) {
    Position::column = c;
}

int Position::getLine() const {
    return line;
}

void Position::setLine(int l) {
    Position::line = l;
}

void Position::addColumn(int count) {
    column += count;
}

void Position::addLine(int count) {
    line += count;
}
