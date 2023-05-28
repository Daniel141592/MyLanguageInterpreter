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
class Typename;

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const Program& program) = 0;
    virtual void visit(const Block& block) = 0;
    virtual void visit(const OrExpression& orExpression) = 0;
    virtual void visit(const AndExpression& andExpression) = 0;
    virtual void visit(const VariableDeclaration& variableDeclaration) = 0;
    virtual void visit(const FunctionDeclaration& functionDeclaration) = 0;
    virtual void visit(const Identifier& identifier) = 0;
    virtual void visit(const Argument& argument) = 0;
    virtual void visit(const Assign& assign) = 0;
    virtual void visit(const IfStatement& ifStatement) = 0;
    virtual void visit(const LoopStatement& loopStatement) = 0;
    virtual void visit(const PatternStatement& patternStatement) = 0;
    virtual void visit(const ReturnStatement& returnStatement) = 0;
    virtual void visit(const FunctionCall& functionCall) = 0;
    virtual void visit(const RelativeExpression& relativeExpression) = 0;
    virtual void visit(const AdditiveExpression& additiveExpression) = 0;
    virtual void visit(const MultiplicationExpression& multiplicationExpression) = 0;
    virtual void visit(const Constant& constant) = 0;
    virtual void visit(const Field& field) = 0;
    virtual void visit(const CastExpression& castExpression) = 0;
    virtual void visit(const Pair& pair) = 0;
    virtual void visit(const NegatedExpression& negatedExpression) = 0;
    virtual void visit(const MatchExpression& matchExpression) = 0;
    virtual void visit(const MatchPair& matchPair) = 0;
    virtual void visit(const MatchType& matchType) = 0;
    virtual void visit(const MatchNone& matchNone) = 0;
    virtual void visit(const Typename& type) = 0;
};

#endif //CODE_VISITOR_H
