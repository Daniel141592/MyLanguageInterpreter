#include "MyLangParser.h"

MyLangParser::MyLangParser(std::unique_ptr<Lexer> l, Parser::HandlerType onError) : lexer(std::move(l)), errorHandler(std::move(onError)) {
    currentToken = lexer->nextToken();
}

void MyLangParser::nextToken() {
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
    throw std::exception();
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
 * single_instruction = (function_declaration | variable_declaration | assign_or_function_call)
 */
std::optional<MyLangParser::SingleInstructionPtr> MyLangParser::parseSingleInstruction(std::unordered_map<std::string,
                                                                                       FunctionDeclaration>& functions) {
    std::optional<SingleInstructionPtr> instruction = parseFunctionDeclaration(functions);
    if (!instruction)
        instruction = parseVariableDeclarationOrAssignOrFunctionCall();
    if (instruction) {
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
 * variable_declaration	    = ["mut"], identifier, ["=”, (expression | pair)], ";"
 * assign_or_function_call	= identifier, (assign | function_call), ";"
 * assign                   = "=", (expression | pair)
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
        if (!consumeIf(TokenType::ASSIGN)) {
            if (!consumeIf(TokenType::SEMICOLON))
                errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
            return std::make_unique<VariableDeclaration>(VariableDeclaration(std::move(identifier.value()), mut));
        }

        std::optional<ExpressionPtr> expression;
        expression = parseExpressionOrPair();
        if (!expression) {
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        }
        if (!consumeIf(TokenType::SEMICOLON))
            errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
        return std::make_unique<VariableDeclaration>(VariableDeclaration(std::move(identifier.value()),
                                                                         std::move(expression.value()), mut));
    }

    std::optional<SingleInstructionPtr> instruction = parseFunctionCall(identifier.value()->getName());
    if (instruction) {
        if (!consumeIf(TokenType::SEMICOLON))
            errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
        return instruction;
    }
    if (!consumeIf(TokenType::ASSIGN))
        criticalError(ErrorType::ASSIGN_OR_FUNCTION_CALL_EXPECTED);
    std::optional<ExpressionPtr> expression;
    expression = parseExpressionOrPair();
    if (!expression) {
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    }
    if (!consumeIf(TokenType::SEMICOLON))
        errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
    return std::make_unique<Assign>(std::move(identifier.value()), std::move(expression.value()));
}

/*
 * pair = expression, expression
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseExpressionOrPair() {
    std::optional<ExpressionPtr> first = parseExpression();
    if (!first)
        return {};
    if (!consumeIf(TokenType::COMMA))
        return first;
    std::optional<ExpressionPtr> second = parseExpression();
    if (!second)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    return std::make_unique<Pair>(std::move(first.value()), std::move(second.value()));
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
std::optional<MyLangParser::FunctionCallPtr> MyLangParser::parseFunctionCall(const std::string& identifier) {
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
 * match_statement = "match", (match_expression | match_pair | match_string | match_float | match_int | match_none)
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

/*
 * match_none = "none", block
 */
std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchNone() {
    if (!consumeIf(TokenType::NONE_KEYWORD))
        return {};
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchNone>(std::move(block.value()));
}

/*
 * match_expression		= expression, ”(”, identifier, ”)”, block
 * match_pair			= pair, block
 */
std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchPairOrExpression() {
    std::optional<ExpressionPtr> expression = parseExpression();
    if (!expression)
        return {};
    if (consumeIf(TokenType::COMMA))
        return parseMatchPair(std::move(expression.value()));
    return parseMatchExpression(std::move(expression.value()));
}

/*
 * match_pair = expression, ",”, expression, block
 */
std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchPair(MyLangParser::ExpressionPtr first) {
    std::optional<ExpressionPtr> second = parseExpression();
    if (!second)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    std::optional<BlockPtr> block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchPair>(std::move(block.value()), std::move(first),std::move(second.value()));
}

/*
 * match_expression	= expression, ”(”, identifier, ”)”, block
 */
std::optional<MyLangParser::MatchStatementPtr> MyLangParser::parseMatchExpression(MyLangParser::ExpressionPtr expression) {
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
    return std::make_unique<MatchExpression>(std::move(expression), std::move(identifier.value()),
                                             std::move(block.value()));
}

/*
 * return_statement	= ”return”, [expression], ”;”
 */
std::optional<MyLangParser::StatementPtr> MyLangParser::parseReturnStatement() {
    if (!consumeIf(TokenType::RETURN_KEYWORD))
        return {};
    std::optional<ExpressionPtr> expression = parseExpression();
    if (!consumeIf(TokenType::SEMICOLON))
        criticalError(ErrorType::MISSING_SEMICOLON);
    if (expression)
        return std::make_unique<ReturnStatement>(std::move(expression.value()));
    return std::make_unique<ReturnStatement>();
}

/*
 * expression = and_expression, {"||”, and_expression}
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseExpression() {
    std::optional<ExpressionPtr> left = parseAndExpression();
    if (!left)
        return {};
    while (consumeIf(TokenType::OR)) {
        std::optional<ExpressionPtr> right = parseAndExpression();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<OrExpression>(currentToken->getPosition(), std::move(left.value()),
                                              std::move(right.value()));
    }
    return left;
}

/*
 * and_expression = relative_expression, {"&&”, relative_expression}
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseAndExpression() {
    std::optional<ExpressionPtr> left = parseRelativeExpression();
    if (!left)
        return {};
    while (consumeIf(TokenType::AND)) {
        std::optional<ExpressionPtr> right = parseRelativeExpression();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<AndExpression>(currentToken->getPosition(), std::move(left.value()),
                                              std::move(right.value()));
    }
    return left;
}

/*
 * relative_expression = (numeric_expression, {operator, numeric_expression}) | is_expression
 * is_expression       = numeric_expression, {”is”, numeric_expression}
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseRelativeExpression() {
    std::optional<ExpressionPtr> left = parseNumericExpression();
    if (!left)
        return {};
    std::optional<RelativeType> relativeType;
    while ((relativeType = checkRelativeType())) {
        nextToken();
        std::optional<ExpressionPtr> right = relativeType == RelativeType::IS
                                      ? parseNumericPair() : parseNumericExpression();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<RelativeExpression>(currentToken->getPosition(), std::move(left.value()),
                                                    std::move(right.value()), relativeType.value());
    }
    return left;
}

/*
 * numeric_expression = term, {("+” | "-”), term }
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseNumericExpression() {
    std::optional<ExpressionPtr> left = parseTerm();
    if (!left)
        return {};
    std::optional<AdditiveType> additiveType;
    while ((additiveType = checkAdditiveType())) {
        nextToken();
        std::optional<ExpressionPtr> right = parseTerm();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<AdditiveExpression>(currentToken->getPosition(), std::move(left.value()),
                                                    std::move(right.value()), additiveType.value());
    }
    return left;
}

/*
 * numeric_pair	= numeric_expression, ",", numeric_expression
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseNumericPair() {
    std::optional<ExpressionPtr> first = parseNumericExpression();
    if (!first)
        return {};
    if (!consumeIf(TokenType::COMMA))
        return first;
    std::optional<ExpressionPtr> second = parseExpression();
    if (!second)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    return std::make_unique<Pair>(std::move(first.value()), std::move(second.value()));
}

/*
 * term	= factor, {("*” | "/” | "//” | "%”), factor};
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseTerm() {
    std::optional<ExpressionPtr> left = parseFactor();
    if (!left)
        return {};
    std::optional<MultiplicativeType> multiplicativeType;
    while ((multiplicativeType = checkMultiplicationType())) {
        nextToken();
        std::optional<ExpressionPtr> right = parseFactor();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<MultiplicationExpression>(currentToken->getPosition(), std::move(left.value()),
                                                    std::move(right.value()), multiplicativeType.value());
    }
    return left;
}

/*
 * factor = ["!" |"-"], constant | typename | id_or_function_call | field | cast_or_nested
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseFactor() {
    bool negated = false;
    if (consumeIf(TokenType::NEGATION) || consumeIf(TokenType::MINUS))
        negated = true;
    std::optional<ExpressionPtr> expression = parseConstant();
    if (!expression)
        expression = parseTypename();
    if (!expression)
        expression = parseIdentifierOrFunctionCall();
    if (!expression)
        expression = parseCastOrNestedExpression();
    if (!expression && negated)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    if (negated)
        return std::make_unique<NegatedExpression>(std::move(expression.value()));
    return expression;
}

/*
 * constant	= number | string
 * number	= int | float
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseConstant() {
    std::optional<ConstantType> constantType = checkConstantType();
    if (!constantType)
        return {};
    if (constantType == ConstantType::INTEGER) {
        int value = std::get<int>(currentToken->getValue());
        nextToken();
        return std::make_unique<Constant>(currentToken->getPosition(), value);
    }
    if (constantType == ConstantType::FLOAT) {
        double value = std::get<double>(currentToken->getValue());
        nextToken();
        return std::make_unique<Constant>(currentToken->getPosition(), value);
    }
    if (constantType == ConstantType::STRING) {
        std::string value = std::get<std::string>(currentToken->getValue());
        nextToken();
        return std::make_unique<Constant>(currentToken->getPosition(), value);
    }
    return {};
}

/*
 * typename	= ”String” | ”Float” | ”Int”
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseTypename() {
    Position position = currentToken->getPosition();
    std::optional<ConstantType> type = checkTypeName();
    if (type)
        nextToken();
    else
        return {};
    return std::make_unique<Typename>(position, type.value());
}

/*
 * id_or_function_call = identifier, [function_call]
 * field = id_or_function_call, ”.”, ”first” | ”second”
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseIdentifierOrFunctionCall() {
    std::optional<ExpressionPtr> expression;
    std::optional<IdentifierPtr> identifier = parseIdentifier();
    if (!identifier)
        return {};
    std::optional<ExpressionPtr> functionCall = std::move(parseFunctionCall(identifier.value()->getName()));
    if (!functionCall)
        expression = std::move(identifier);
    else
        expression = std::move(functionCall);
    std::optional<ExpressionPtr> field = parseField(expression.value());
    if (!field)
        return expression;
    return field;
}

/*
 * field = id_or_function_call, ”.”, ”first” | ”second”
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseField(ExpressionPtr& expression) {
    if (!consumeIf(TokenType::DOT))
        return {};
    if (consumeIf(TokenType::FIRST_KEYWORD))
        return std::make_unique<Field>(currentToken->getPosition(), std::move(expression), FieldType::FIRST);
    if (consumeIf(TokenType::SECOND_KEYWORD))
        return std::make_unique<Field>(currentToken->getPosition(), std::move(expression), FieldType::SECOND);
    criticalError(ErrorType::FIRST_OR_SECOND_EXPECTED);
    return {};
}

/*
 * identifier = (letter | ”_”), {letter | digit | ”_”}
 */
std::optional<MyLangParser::IdentifierPtr> MyLangParser::parseIdentifier() {
    if (currentToken->getType() != TokenType::IDENTIFIER)
        return {};
    Position position = currentToken->getPosition();
    std::string name = std::get<std::string>(currentToken->getValue());
    nextToken();
    return std::make_unique<Identifier>(position, name);
}

/*
 * cast_or_nested = [cast], "(", expression, ")”
 * cast			  = ”String” | ”Float” | ”Int” )
 */
std::optional<MyLangParser::ExpressionPtr> MyLangParser::parseCastOrNestedExpression() {
    Position position = currentToken->getPosition();
    std::optional<ConstantType> castType = checkTypeName();
    if (castType)
        nextToken();
    if (!consumeIf(TokenType::LEFT_BRACKET)) {
        if (castType)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        else
            return {};
    }
    std::optional<ExpressionPtr> expression = parseExpression();
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    if (castType)
        return std::make_unique<CastExpression>(position, std::move(expression.value()), castType.value());
    return expression;
}

std::optional<RelativeType> MyLangParser::checkRelativeType() {
    switch (currentToken->getType()) {
        case TokenType::GREATER_OR_EQUAL:
            return RelativeType::GREATER_EQUAL;
        case TokenType::GREATER_THAN:
            return RelativeType::GREATER;
        case TokenType::EQUAL:
            return RelativeType::EQUAL;
        case TokenType::LESS_OR_EQUAL:
            return RelativeType::LESS_EQUAL;
        case TokenType::LESS_THAN:
            return RelativeType::LESS;
        case TokenType::NOT_EQUAL:
            return RelativeType::NOT_EQUAL;
        case TokenType::IS_KEYWORD:
            return RelativeType::IS;
        default:
            return {};
    }
}

std::optional<AdditiveType> MyLangParser::checkAdditiveType() {
    switch (currentToken->getType()) {
        case TokenType::PLUS:
            return AdditiveType::ADD;
        case TokenType::MINUS:
            return AdditiveType::SUBTRACT;
        default:
            return {};
    }
}

std::optional<MultiplicativeType> MyLangParser::checkMultiplicationType() {
    switch (currentToken->getType()) {
        case TokenType::ASTERISK:
            return MultiplicativeType::MULTIPLY;
        case TokenType::DIVISION:
            return MultiplicativeType::DIVIDE;
        case TokenType::INT_DIVISION:
            return MultiplicativeType::INT_DIVIDE;
        case TokenType::MODULO:
            return MultiplicativeType::MODULO;
        default:
            return {};
    }
}

std::optional<ConstantType> MyLangParser::checkTypeName() {
    switch (currentToken->getType()) {
        case TokenType::INT_KEYWORD:
            return ConstantType::INTEGER;
        case TokenType::FLOAT_KEYWORD:
            return ConstantType::FLOAT;
        case TokenType::STRING_KEYWORD:
            return ConstantType::STRING;
        default:
            return {};
    }
}

std::optional<ConstantType> MyLangParser::checkConstantType() {
    switch (currentToken->getType()) {
        case TokenType::INTEGER_VALUE:
            return ConstantType::INTEGER;
        case TokenType::FLOAT_VALUE:
            return ConstantType::FLOAT;
        case TokenType::STRING_LITERAL:
            return ConstantType::STRING;
        default:
            return {};
    }
}

