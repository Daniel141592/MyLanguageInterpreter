#ifndef CODE_VISITOR_H
#define CODE_VISITOR_H

class Program;
class Block;
class OrExpression;
class VariableDeclaration;
class FunctionDeclaration;
class Identifier;
class Argument;
class Assign;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const Program* program) const = 0;
    virtual void visit(const Block* block) const = 0;
    virtual void visit(const OrExpression* singleInstruction) const = 0;
    virtual void visit(const VariableDeclaration* variableDeclaration) const = 0;
    virtual void visit(const FunctionDeclaration* functionDeclaration) const = 0;
    virtual void visit(const Identifier* identifier) const = 0;
    virtual void visit(const Argument* argument) const = 0;
    virtual void visit(const Assign* assign) const = 0;
};

#endif //CODE_VISITOR_H
