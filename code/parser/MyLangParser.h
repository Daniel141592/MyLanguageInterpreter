#ifndef CODE_MYLANGPARSER_H
#define CODE_MYLANGPARSER_H

#include <optional>

#include "Parser.h"
#include "structure/FunctionDeclaration.h"
#include "structure/Statement.h"
#include "structure/SingleInstruction.h"
#include "structure/Block.h"
#include "structure/Declaration.h"
#include "structure/VariableDeclaration.h"
#include "structure/FunctionCall.h"
#include "structure/Identifier.h"
#include "structure/Assign.h"
#include "structure/IfStatement.h"
#include "structure/LoopStatement.h"
#include "structure/PatternStatement.h"
#include "structure/ReturnStatement.h"
#include "structure/MatchStatement.h"
#include "structure/MatchNone.h"
#include "structure/MatchType.h"
#include "structure/MatchPair.h"
#include "structure/MatchExpression.h"
#include "structure/OrExpression.h"
#include "structure/AndExpression.h"
#include "structure/RelativeExpression.h"
#include "structure/AdditiveExpression.h"
#include "structure/MultiplicationExpression.h"
#include "structure/NegatedExpression.h"
#include "structure/CastExpression.h"
#include "structure/Constant.h"
#include "structure/Field.h"
#include "structure/ConstantType.h"
#include "structure/Pair.h"
#include "structure/Typename.h"

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
    bool parseInstruction(std::vector<InstructionPtr>& instructions,
                          std::unordered_map<std::string, FunctionDeclaration>& functions);
    std::optional<BlockPtr> parseBlock();
    std::optional<SingleInstructionPtr> parseSingleInstruction(std::unordered_map<std::string,
                                                               FunctionDeclaration>& functions);
    std::optional<StatementPtr> parseStatement();
    std::optional<SingleInstructionPtr> parseVariableDeclarationOrAssignOrFunctionCall();
    std::optional<SingleInstructionPtr> parseFunctionDeclaration(
            std::unordered_map<std::string, FunctionDeclaration>& functions);
    std::optional<std::vector<Argument>> parseArgumentsList();
    std::optional<Argument> parseArgument();

    std::optional<FunctionCallPtr> parseFunctionCall(const std::string& identifier);
    std::optional<StatementPtr> parseIfStatement();
    std::optional<BlockPtr> parseElseStatement();
    std::optional<StatementPtr> parseLoopStatement();
    std::optional<StatementPtr> parsePatternStatement();
    std::optional<StatementPtr> parseReturnStatement();
    bool parseMatchStatement(std::vector<MatchStatementPtr>& matches);
    std::optional<MatchStatementPtr> parseMatchType();
    std::optional<MatchStatementPtr> parseMatchNone();
    std::optional<MatchStatementPtr> parseMatchPairOrExpression();
    std::optional<MatchStatementPtr> parseMatchPair(ExpressionPtr first);
    std::optional<MatchStatementPtr> parseMatchExpression(ExpressionPtr expression);

    std::optional<ExpressionPtr> parseExpression();
    std::optional<ExpressionPtr> parseExpressionOrPair();
    std::optional<ExpressionPtr> parseAndExpression();
    std::optional<ExpressionPtr> parseRelativeExpression();
    std::optional<ExpressionPtr> parseNumericExpression();
    std::optional<ExpressionPtr> parseNumericPair();
    std::optional<ExpressionPtr> parseTerm();
    std::optional<ExpressionPtr> parseFactor();
    std::optional<ExpressionPtr> parseConstant();
    std::optional<ExpressionPtr> parseTypename();
    std::optional<ExpressionPtr> parseIdentifierOrFunctionCall();
    std::optional<ExpressionPtr> parseField(ExpressionPtr& expression);
    std::optional<ExpressionPtr> parseCastOrNestedExpression();
    std::optional<IdentifierPtr> parseIdentifier();
    std::optional<RelativeType> checkRelativeType();
    std::optional<AdditiveType> checkAdditiveType();
    std::optional<MultiplicativeType> checkMultiplicationType();
    std::optional<ConstantType> checkTypeName();
    std::optional<ConstantType> checkConstantType();

    void nextToken();
    bool consumeIf(TokenType tokenType);
    void criticalError(ErrorType type);
};


#endif //CODE_MYLANGPARSER_H
