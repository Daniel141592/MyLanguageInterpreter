#ifndef CODE_POSITION_H
#define CODE_POSITION_H


class Position {
    int column, line;

public:
    Position();
    Position(int column, int line);

    int getColumn() const;
    void setColumn(int column);
    void addColumn(int = 1);
    int getLine() const;
    void setLine(int line);
    void addLine(int = 1);

    bool operator==(const Position&) const;
};


#endif //CODE_POSITION_H
