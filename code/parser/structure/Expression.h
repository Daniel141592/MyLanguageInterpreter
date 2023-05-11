#ifndef CODE_EXPRESSION_H
#define CODE_EXPRESSION_H


#include <memory>
#include "../Visitable.h"

class Expression : Visitable {
public:
    typedef std::unique_ptr<Expression> ExpressionPtr;
private:
    ExpressionPtr left;
    ExpressionPtr right;
public:
    Expression(ExpressionPtr l, ExpressionPtr r);
    ~Expression() override = default;
    void accept(const Visitor* visitor) const override;

    const ExpressionPtr& getLeft() const;
    const ExpressionPtr& getRight() const;
};


#endif //CODE_EXPRESSION_H
