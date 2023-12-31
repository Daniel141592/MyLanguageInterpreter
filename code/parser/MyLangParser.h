#ifndef CODE_MYLANGPARSER_H
#define CODE_MYLANGPARSER_H

#include <optional>

#include "Parser.h"
#include "../structure/FunctionDeclaration.h"
#include "../structure/Statement.h"
#include "../structure/SingleInstruction.h"
#include "../structure/Block.h"
#include "../structure/Declaration.h"
#include "../structure/VariableDeclaration.h"
#include "../structure/FunctionCall.h"
#include "../structure/Identifier.h"
#include "../structure/Assign.h"
#include "../structure/IfStatement.h"
#include "../structure/LoopStatement.h"
#include "../structure/PatternStatement.h"
#include "../structure/ReturnStatement.h"
#include "../structure/MatchStatement.h"
#include "../structure/MatchNone.h"
#include "../structure/MatchType.h"
#include "../structure/MatchPair.h"
#include "../structure/MatchExpression.h"
#include "../structure/OrExpression.h"
#include "../structure/AndExpression.h"
#include "../structure/RelativeExpression.h"
#include "../structure/AdditiveExpression.h"
#include "../structure/MultiplicationExpression.h"
#include "../structure/NegatedExpression.h"
#include "../structure/CastExpression.h"
#include "../structure/Constant.h"
#include "../structure/Field.h"
#include "../structure/ConstantType.h"
#include "../structure/Pair.h"
#include "../structure/Typename.h"

class MyLangParser : public Parser {
    using InstructionPtr = Instruction::InstructionPtr;
    using SingleInstructionPtr = SingleInstruction::SingleInstructionPtr;
    using StatementPtr = Statement::StatementPtr;
    using BlockPtr = Block::BlockPtr;
    using ExpressionPtr = Expression::ExpressionPtr;
    using IdentifierPtr = Identifier::IdentifierPtr;
    using MatchStatementPtr = MatchStatement::MatchStatementPtr;
    using FunctionCallPtr = FunctionCall::FunctionCallPtr;

    std::unique_ptr<Lexer> lexer;
    HandlerType errorHandler;
    std::optional<Token> currentToken;
public:
    MyLangParser(std::unique_ptr<Lexer> l, HandlerType onError);
    Program parse() override;
private:
    bool parseInstruction(std::vector<InstructionPtr>& instructions);
    BlockPtr parseBlock();
    SingleInstructionPtr parseSingleInstruction();
    StatementPtr parseStatement();
    SingleInstructionPtr parseVariableDeclarationOrAssignOrFunctionCall();
    SingleInstructionPtr parseFunctionDeclaration();
    std::optional<std::vector<Argument>> parseArgumentsList();
    std::optional<Argument> parseArgument();
    FunctionCallPtr parseFunctionCall(const std::string& identifier, const Position& position);
    StatementPtr parseIfStatement();
    BlockPtr parseElseStatement();
    StatementPtr parseLoopStatement();
    StatementPtr parsePatternStatement();
    StatementPtr parseReturnStatement();
    bool parseMatchStatement(std::vector<MatchStatementPtr>& matches);
    MatchStatementPtr parseMatchType();
    MatchStatementPtr parseMatchNone();
    MatchStatementPtr parseMatchPairOrExpression();
    MatchStatementPtr parseMatchPair(ExpressionPtr first);
    MatchStatementPtr parseMatchExpression(ExpressionPtr expression);
    ExpressionPtr parseExpression();
    ExpressionPtr parseExpressionOrPair();
    ExpressionPtr parseAndExpression();
    ExpressionPtr parseRelativeExpression();
    ExpressionPtr parseNumericExpression();
    ExpressionPtr parseNumericPair();
    ExpressionPtr parseTerm();
    ExpressionPtr parseFactor();
    ExpressionPtr parseConstant();
    ExpressionPtr parseIdentifierOrFunctionCall();
    ExpressionPtr parseField(ExpressionPtr& expression, const Position& position);
    ExpressionPtr parseTypenameOrCastOrNestedExpression();
    IdentifierPtr parseIdentifier();

    void nextToken();
    bool consumeIf(TokenType tokenType);
    void criticalError(ErrorType type);
};


#endif //CODE_MYLANGPARSER_H
