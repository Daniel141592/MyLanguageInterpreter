#ifndef CODE_VISITOR_H
#define CODE_VISITOR_H

class Program;
class Block;
class OrExpression;
class AndExpression;
class VariableDeclaration;
class FunctionDeclaration;
class Identifier;
class Argument;
class Assign;
class IfStatement;
class LoopStatement;
class PatternStatement;
class ReturnStatement;
class FunctionCall;
class RelativeExpression;
class AdditiveExpression;
class MultiplicationExpression;
class Constant;
class Field;
class CastExpression;
class NegatedExpression;
class MatchExpression;
class MatchPair;
class MatchType;
class MatchNone;
class Pair;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const Program* program) const = 0;
    virtual void visit(const Block* block) const = 0;
    virtual void visit(const OrExpression* orExpression) const = 0;
    virtual void visit(const AndExpression* andExpression) const = 0;
    virtual void visit(const VariableDeclaration* variableDeclaration) const = 0;
    virtual void visit(const FunctionDeclaration* functionDeclaration) const = 0;
    virtual void visit(const Identifier* identifier) const = 0;
    virtual void visit(const Argument* argument) const = 0;
    virtual void visit(const Assign* assign) const = 0;
    virtual void visit(const IfStatement* ifStatement) const = 0;
    virtual void visit(const LoopStatement* loopStatement) const = 0;
    virtual void visit(const PatternStatement* patternStatement) const = 0;
    virtual void visit(const ReturnStatement* returnStatement) const = 0;
    virtual void visit(const FunctionCall* functionCall) const = 0;
    virtual void visit(const RelativeExpression* relativeExpression) const = 0;
    virtual void visit(const AdditiveExpression* additiveExpression) const = 0;
    virtual void visit(const MultiplicationExpression* multiplicationExpression) const = 0;
    virtual void visit(const Constant* constant) const = 0;
    virtual void visit(const Field* field) const = 0;
    virtual void visit(const CastExpression* castExpression) const = 0;
    virtual void visit(const Pair* pair) const = 0;
    virtual void visit(const NegatedExpression* negatedExpression) const = 0;
    virtual void visit(const MatchExpression* matchExpression) const = 0;
    virtual void visit(const MatchPair* matchPair) const = 0;
    virtual void visit(const MatchType* matchType) const = 0;
    virtual void visit(const MatchNone* matchNone) const = 0;
};

#endif //CODE_VISITOR_H
