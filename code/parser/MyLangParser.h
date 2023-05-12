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

class MyLangParser : public Parser {
    using InstructionPtr = Instruction::InstructionPtr;
    using SingleInstructionPtr = SingleInstruction::SingleInstructionPtr;
    using StatementPtr = Statement::StatementPtr;
    using BlockPtr = Block::BlockPtr;
    using ExpressionPtr = Expression::ExpressionPtr;
    using IdentifierPtr = Identifier::IdentifierPtr;
    using MatchStatementPtr = MatchStatement::MatchStatementPtr;

    std::unique_ptr<Lexer> lexer;
    HandlerType errorHandler;
    std::optional<Token> currentToken;
    std::optional<Token> previousToken;
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

    std::optional<SingleInstructionPtr> parseFunctionCall(const std::string& identifier);
    std::optional<StatementPtr> parseIfStatement();
    std::optional<BlockPtr> parseElseStatement();
    std::optional<StatementPtr> parseLoopStatement();
    std::optional<StatementPtr> parsePatternStatement();
    std::optional<StatementPtr> parseReturnStatement();
    bool parseMatchStatement(std::vector<MatchStatementPtr>& matches);
    std::optional<MatchStatementPtr> parseMatchType();
    std::optional<MatchStatementPtr> parseMatchNone();
    std::optional<MatchStatementPtr> parseMatchPairOrExpression();

    std::optional<ExpressionPtr> parseExpression();
    std::optional<IdentifierPtr> parseIdentifier();


    void nextToken();
    bool consumeIf(TokenType tokenType);
    void criticalError(ErrorType type);
};


#endif //CODE_MYLANGPARSER_H
