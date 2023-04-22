#ifndef CODE_POSITION_H
#define CODE_POSITION_H


class Position {
    int column, line;

public:
    Position();
    Position(int, int);

    int getColumn() const;
    void setColumn(int column);
    void addColumn(int = 1);
    int getLine() const;
    void setLine(int line);
    void addLine(int = 1);
};


#endif //CODE_POSITION_H
