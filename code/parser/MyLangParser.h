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
#include "structure/FunctionDeclaration.h"
#include "structure/Identifier.h"

class MyLangParser : public Parser {
    using InstructionPtr = Instruction::InstructionPtr;
    using SingleInstructionPtr = SingleInstruction::SingleInstructionPtr;
    using StatementPtr = Statement::StatementPtr;
    using BlockPtr = Block::BlockPtr;
    using ExpressionPtr = Expression::ExpressionPtr;
    using IdentifierPtr = Identifier::IdentifierPtr;

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
    std::optional<SingleInstructionPtr> parseSingleInstruction(std::unordered_map<std::string, FunctionDeclaration>& functions);
    std::optional<StatementPtr> parseStatement();
    std::optional<SingleInstructionPtr> parseDeclaration(std::unordered_map<std::string, FunctionDeclaration>& functions);
    std::optional<SingleInstructionPtr> parseVariableDeclaration();
    std::optional<SingleInstructionPtr> parseFunctionDeclaration(
            std::unordered_map<std::string, FunctionDeclaration>& functions);
    std::optional<std::vector<Argument>> parseArgumentsList();

    std::optional<SingleInstructionPtr> parseAssign();
    std::optional<SingleInstructionPtr> parseFunctionCall();
    std::optional<StatementPtr> parseIfStatement();
    std::optional<StatementPtr> parseLoopStatement();
    std::optional<StatementPtr> parsePatternStatement();
    std::optional<StatementPtr> parseReturnStatement();

    std::optional<ExpressionPtr> parseExpression();
    std::optional<Identifier> parseIdentifier();


    void nextToken();
    bool consumeIf(TokenType tokenType);
    void criticalError(ErrorType type);
};


#endif //CODE_MYLANGPARSER_H
