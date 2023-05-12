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
 * single_instruction = (function_declaration | variable_declaration | assign_or_function_call), ”;”
 */
std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseSingleInstruction(std::unordered_map<std::string,
                                                                                       FunctionDeclaration>& functions) {
    std::optional<SingleInstructionPtr> instruction = parseFunctionDeclaration(functions);
    if (!instruction)
        instruction = parseVariableDeclarationOrAssignOrFunctionCall();
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
 * variable_declaration	    = ["mut"], identifier, ["=”, expression]
 * assign_or_function_call	= identifier, (assign | function_call)
 * assign                   = "=", expression
 */
std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseVariableDeclarationOrAssignOrFunctionCall() {
    bool mut = false;
    if (consumeIf(TokenType::MUT_KEYWORD))
        mut = true;
    std::optional<IdentifierPtr> identifier = parseIdentifier();
    if (!identifier) {
        if (!mut)
            return {};
        criticalError(ErrorType::MUT_OUTSIDE_DECLARATION);
    }
    if (mut) {
        if (!consumeIf(TokenType::ASSIGN))
            return std::make_unique<VariableDeclaration>(VariableDeclaration(std::move(identifier.value()), mut));

        std::optional<ExpressionPtr> expression;
        expression = parseExpression();
        if (!expression) {
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        }
        return std::make_unique<VariableDeclaration>(VariableDeclaration(std::move(identifier.value()),
                                                                         std::move(expression.value()), mut));
    }

    std::optional<SingleInstructionPtr> instruction = parseFunctionCall(identifier.value()->getName());
    if (instruction)
        return instruction;
    if (!consumeIf(TokenType::ASSIGN))
        criticalError(ErrorType::ASSIGN_OR_FUNCTION_CALL_EXPECTED);
    std::optional<ExpressionPtr> expression;
    expression = parseExpression();
    if (!expression) {
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    }
    // TODO rozdzielić assign od declaration
    return std::make_unique<Assign>(std::move(identifier.value()), std::move(expression.value()));
}

/*
 * function_declaration	= ”func”, identifier, arguments_list, block
 */
std::optional<MyLangParser::SingleInstructionPtr>
MyLangParser::parseFunctionDeclaration(std::unordered_map<std::string, FunctionDeclaration> &functions) {
    if (!consumeIf(TokenType::FUNC_KEYWORD))
        return {};
    Position position = currentToken->getPosition();
    std::optional<IdentifierPtr> identifier = parseIdentifier();
    if (!identifier)
        criticalError(ErrorType::IDENTIFIER_EXPECTED);
    auto it = functions.find(identifier.value()->getName());
    if (it != functions.end())
        criticalError(ErrorType::FUNCTION_REDEFINITION);
    std::optional<std::vector<Argument>> args = parseArgumentsList();
    if (!args)
        criticalError(ErrorType::ARGUMENTS_LIST_EXPECTED);
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    FunctionDeclaration functionDeclaration(position, identifier.value()->getName(),
                                            std::move(block.value()), std::move(args.value()));
    return std::make_unique<FunctionDeclaration>(std::move(functionDeclaration));
}

/*
 * arguments_list = ”(", [argument, {",", argument}], ”)”
 */
std::optional<std::vector<Argument>> MyLangParser::parseArgumentsList() {
    if (!consumeIf(TokenType::LEFT_BRACKET))
        return {};
    std::optional<Argument> firstArgument = parseArgument();
    std::vector<Argument> args;
    if (!firstArgument) {
        if (!consumeIf(TokenType::RIGHT_BRACKET))
            criticalError(ErrorType::BRACKET_EXPECTED);
        return std::vector<Argument>();
    }
    args.push_back(firstArgument.value());
    while (consumeIf(TokenType::COMMA)) {
        std::optional<Argument> arg = parseArgument();
        if (!arg)
            criticalError(ErrorType::IDENTIFIER_EXPECTED);
        args.push_back(arg.value());
    }
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    return args;
}

/*
 * argument = [”ref”], identifier
 */
std::optional<Argument> MyLangParser::parseArgument() {
    bool ref = false;
    if (consumeIf(TokenType::REF_KEYWORD))
        ref = true;
    std::optional<IdentifierPtr> identifier = parseIdentifier();
    if (!identifier) {
        if (ref)
            criticalError(ErrorType::IDENTIFIER_EXPECTED);
        return {};
    }
    return Argument(currentToken->getPosition(), identifier.value()->getName(), ref);
}

/*
 * function_call = "(", [expression, {",", expression}], ”)”
 */
std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseFunctionCall(const std::string& identifier) {
    if (!consumeIf(TokenType::LEFT_BRACKET))
        return {};
    std::optional<ExpressionPtr> firstArgument = parseExpression();
    if (!firstArgument) {
        if (!consumeIf(TokenType::RIGHT_BRACKET))
            criticalError(ErrorType::BRACKET_EXPECTED);
        return std::make_unique<FunctionCall>(
                Identifier(currentToken->getPosition(), identifier), std::vector<ExpressionPtr>());
    }
    std::vector<ExpressionPtr> args;
    args.emplace_back(std::move(firstArgument.value()));
    while (consumeIf(TokenType::COMMA)) {
        std::optional<ExpressionPtr> arg = parseExpression();
        if (!arg)
            criticalError(ErrorType::IDENTIFIER_EXPECTED);
        args.emplace_back(std::move(arg.value()));
    }
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    return std::make_unique<FunctionCall>(
            Identifier(currentToken->getPosition(), identifier),
            std::move(args)
    );
}

/*
 * if_statement	= "if”, expression, block, [else_statement]
 */
std::optional<MyLangParser::StatementPtr> MyLangParser::parseIfStatement() {
    if (!consumeIf(TokenType::IF_KEYWORD))
        return {};
    std::optional<ExpressionPtr> expression = parseExpression();
    if (!expression)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    std::optional<BlockPtr> ifBlock = parseBlock();
    if (!ifBlock)
        criticalError(ErrorType::BLOCK_EXPECTED);
    std::optional<BlockPtr> elseBlock = parseElseStatement();
    if (!elseBlock)
        return std::make_unique<IfStatement>(std::move(expression.value()), std::move(ifBlock.value()));
    return std::make_unique<IfStatement>(std::move(expression.value()),
                                         std::move(ifBlock.value()), std::move(elseBlock.value()));
}

/*
 * else_statement = "else”, block
 */
std::optional<MyLangParser::BlockPtr> MyLangParser::parseElseStatement() {
    if (!consumeIf(TokenType::ELSE_KEYWORD))
        return {};
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return block;
}

/*
 * loop_statement = "loop”, expression, block
 */
std::optional<MyLangParser::StatementPtr> MyLangParser::parseLoopStatement() {
    if (!consumeIf(TokenType::LOOP_KEYWORD))
        return {};
    std::optional<ExpressionPtr> expression = parseExpression();
    if (!expression)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<LoopStatement>(std::move(expression.value()), std::move(block.value()));
}

/*
 * pattern_statement = "pattern”, expression, "{", {match_statement}, ”}”
 */
std::optional<MyLangParser::StatementPtr> MyLangParser::parsePatternStatement() {
    if (!consumeIf(TokenType::PATTERN_KEYWORD))
        return {};
    std::optional<ExpressionPtr> expression = parseExpression();
    if (!expression)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    if (!consumeIf(TokenType::LEFT_PARENTHESIS))
        criticalError(ErrorType::MISSING_PARENTHESIS);
    std::vector<MatchStatement::MatchStatementPtr> matches;
    while (parseMatchStatement(matches));
    if (!consumeIf(TokenType::RIGHT_PARENTHESIS))
        criticalError(ErrorType::MISSING_PARENTHESIS);
    return std::make_unique<PatternStatement>(std::move(expression.value()), std::move(matches));
}

/*
 * match_statement = "match", (match_expression | match_pair | match_string | match_float | match_int | "none”)
 */
bool MyLangParser::parseMatchStatement(std::vector<MatchStatement::MatchStatementPtr>& matches) {
    if (!consumeIf(TokenType::MATCH_KEYWORD))
        return false;
    std::optional<MatchStatementPtr> statement = parseMatchType();
    if (!statement)
        statement = parseMatchNone();
    if (!statement)
        statement = parseMatchPairOrExpression();
    if (!statement)
        criticalError(ErrorType::INVALID_MATCH_SYNTAX);
    matches.emplace_back(std::move(statement.value()));
    return true;
}

/*
 * match_string	= "String”, ”(”, identifier, ”)”, block
 * match_float  = "Float”, ”(”, identifier, ”)”, block
 * match_int	= "Int”, ”(”, identifier, ”)”, block
 */
std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchType() {
    ConstantType type;
    if (consumeIf(TokenType::STRING_KEYWORD))
        type = ConstantType::STRING;
    else if (consumeIf(TokenType::INT_KEYWORD))
        type = ConstantType::INTEGER;
    else if (consumeIf(TokenType::FLOAT_KEYWORD))
        type = ConstantType::FLOAT;
    else
        return {};
    if (!consumeIf(TokenType::LEFT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    std::optional<IdentifierPtr> identifier = parseIdentifier();
    if (!identifier)
        criticalError(ErrorType::IDENTIFIER_EXPECTED);
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchType>(std::move(block.value()), std::move(identifier.value()), type);
}

std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchNone() {
    return {};
}


std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchPairOrExpression() {
    return {};
}


std::optional<MyLangParser::StatementPtr> MyLangParser::parseReturnStatement() {
    return {};
}

std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseExpression() {
    return {};
}

std::optional<MyLangParser::IdentifierPtr> MyLangParser::parseIdentifier() {
    return {};
}