#include "MyLangParser.h"

MyLangParser::MyLangParser(std::unique_ptr<Lexer> l, Parser::HandlerType onError) : lexer(std::move(l)), errorHandler(std::move(onError)) {
    currentToken = lexer->nextToken();
}

void MyLangParser::nextToken() {
    previousToken = currentToken;
    currentToken = lexer->nextToken();
}

bool MyLangParser::consumeIf(TokenType tokenType) {
    if (currentToken && currentToken.value().getType() == tokenType) {
        nextToken();
        return true;
    }
    return false;
}

void MyLangParser::criticalError(ErrorType type) {
    errorHandler(currentToken->getPosition(), type);  // TODO błąd krytyczny
}

/*
 * program = instruction, {instruction}
 */
Program MyLangParser::parse() {
    std::vector<InstructionPtr> instructions;
    std::unordered_map<std::string, FunctionDeclaration> functions;
    while (parseInstruction(instructions, functions));

    Program program(std::move(instructions));
    return program;
}

/*
 * instruction = block | single_instruction | statement
 */
bool MyLangParser::parseInstruction(std::vector<InstructionPtr>& instructions, std::unordered_map<std::string,
                                    FunctionDeclaration>& functions) {
    std::optional<InstructionPtr> instruction = parseBlock();
    if (!instruction)
        instruction = parseSingleInstruction(functions);
    if (!instruction)
        instruction = parseStatement();
    if (instruction) {
        instructions.emplace_back(std::move(instruction.value()));
        return true;
    }
    return false;
}

/*
 * block = ”{”, {instruction}, ”}”
 */
std::optional<MyLangParser::BlockPtr> MyLangParser::parseBlock() {
    std::vector<InstructionPtr> instructions;
    std::unordered_map<std::string, FunctionDeclaration> functions;
    if (consumeIf(TokenType::LEFT_PARENTHESIS)) {
        while (parseInstruction(instructions, functions));
        if (!consumeIf(TokenType::RIGHT_PARENTHESIS))
            criticalError(ErrorType::MISSING_PARENTHESIS);
        return std::make_unique<Block>(std::move(instructions));
    }
    return {};
}

/*
 * single_instruction = (declaration | assign | function_call), ”;”
 */
std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseSingleInstruction(std::unordered_map<std::string,
                                                                                       FunctionDeclaration>& functions) {
    std::optional<SingleInstructionPtr> instruction = parseDeclaration(functions);
    if (!instruction)
        instruction = parseAssign();
    if (!instruction)
        instruction = parseFunctionCall();
    if (instruction) {
        if (!consumeIf(TokenType::SEMICOLON))
            errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
        return instruction;
    }
    return {};
}

/*
 * statement = if_statement | loop_statement | pattern_statement | return_statement
 */
std::optional<MyLangParser::StatementPtr> MyLangParser::parseStatement() {
    std::optional<StatementPtr> instruction = parseIfStatement();
    if (!instruction)
        instruction = parseLoopStatement();
    if (!instruction)
        instruction = parsePatternStatement();
    if (!instruction)
        instruction = parseReturnStatement();
    if (instruction)
        return instruction;
    return {};
}

/*
 * declaration = variable_declaration | function_declaration
 */
std::optional<MyLangParser::SingleInstructionPtr>
MyLangParser::parseDeclaration(std::unordered_map<std::string, FunctionDeclaration> &functions) {
    std::optional<SingleInstructionPtr> instruction = parseVariableDeclaration();
    if (!instruction)
        instruction = parseFunctionDeclaration(functions);
    if (instruction)
        return instruction;
    return {};
}

/*
 * variable_declaration	= ["mut"], identifier, ["=”, expression]
 */
std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseVariableDeclaration() {
    bool mut = false;
    if (consumeIf(TokenType::MUT_KEYWORD))
        mut = true;
    std::optional<Identifier> identifier = parseIdentifier();
    if (!identifier) {
        if (mut) {
            criticalError(ErrorType::MUT_OUTSIDE_DECLARATION);
        }
        return {};
    }

    std::optional<ExpressionPtr> expression;
    if (consumeIf(TokenType::ASSIGN)) {
        expression = parseExpression();
        if (!expression)
            errorHandler(currentToken->getPosition(), ErrorType::EXPRESSION_EXPECTED);
    }
    if (expression)
        return std::make_unique<VariableDeclaration>(VariableDeclaration(identifier.value(),
                                                                         std::move(expression.value()), mut));
    return std::make_unique<VariableDeclaration>(VariableDeclaration(identifier.value(), mut));
}

/*
 * function_declaration	= ”func”, identifier, arguments_list, block
 */
std::optional<MyLangParser::SingleInstructionPtr>
MyLangParser::parseFunctionDeclaration(std::unordered_map<std::string, FunctionDeclaration> &functions) {
    if (!consumeIf(TokenType::FUNC_KEYWORD))
        return {};
    Position position = currentToken->getPosition();
    std::optional<Identifier> identifier = parseIdentifier();
    if (!identifier)
        criticalError(ErrorType::IDENTIFIER_EXPECTED);
    auto it = functions.find(identifier->getName());
    if (it != functions.end())
        criticalError(ErrorType::FUNCTION_REDEFINITION);
    std::optional<std::vector<Argument>> args = parseArgumentsList();
    if (!args)
        criticalError(ErrorType::ARGUMENTS_LIST_EXPECTED);
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    FunctionDeclaration functionDeclaration(position, identifier->getName(),
                                            std::move(block.value()), std::move(args.value()));
    return std::make_unique<FunctionDeclaration>(std::move(functionDeclaration));
}

/*
 * arguments_list = ”(", [argument, {",", argument}], ”)”
 */
std::optional<std::vector<Argument>> MyLangParser::parseArgumentsList() {
//    if (!consumeIf(TokenType::LEFT_BRACKET))
    return {};
}

std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseAssign() {
    return {};
}

std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseFunctionCall() {
    return {};
}

std::optional<MyLangParser::StatementPtr> MyLangParser::parseIfStatement() {
    return {};
}

std::optional<MyLangParser::StatementPtr> MyLangParser::parseLoopStatement() {
    return {};
}

std::optional<MyLangParser::StatementPtr> MyLangParser::parsePatternStatement() {
    return {};
}

std::optional<MyLangParser::StatementPtr> MyLangParser::parseReturnStatement() {
    return {};
}

std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseExpression() {
    return {};
}

std::optional<Identifier> MyLangParser::parseIdentifier() {
    return {};
}


