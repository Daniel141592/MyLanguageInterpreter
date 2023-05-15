#ifndef CODE_EXPRESSION_H
#define CODE_EXPRESSION_H

#include <memory>
#include "../Visitable.h"
#include "../../Position.h"

class Expression : public Visitable {
protected:
    Position position;
    explicit Expression(Position p);
public:
    using ExpressionPtr = std::unique_ptr<Expression>;
    ~Expression() override = default;

    const Position &getPosition() const;

    void accept(Visitor* visitor) const override = 0;
};

#endif //CODE_EXPRESSION_H
