#include "MyLangParser.h"

namespace {
    const std::unordered_map<TokenType, RelativeType> relativeTypes = {
            {TokenType::GREATER_OR_EQUAL, RelativeType::GREATER_EQUAL},
            {TokenType::GREATER_THAN, RelativeType::GREATER},
            {TokenType::EQUAL, RelativeType::EQUAL},
            {TokenType::LESS_OR_EQUAL, RelativeType::LESS_EQUAL},
            {TokenType::LESS_THAN, RelativeType::LESS},
            {TokenType::NOT_EQUAL, RelativeType::NOT_EQUAL},
            {TokenType::IS_KEYWORD, RelativeType::IS}
    };

    const std::unordered_map<TokenType, AdditiveType> additiveTypes = {
            {TokenType::PLUS, AdditiveType::ADD},
            {TokenType::MINUS, AdditiveType::SUBTRACT}
    };

    const std::unordered_map<TokenType, MultiplicativeType> multiplicativeTypes = {
            {TokenType::ASTERISK, MultiplicativeType::MULTIPLY},
            {TokenType::DIVISION, MultiplicativeType::DIVIDE},
            {TokenType::INT_DIVISION, MultiplicativeType::INT_DIVIDE},
            {TokenType::MODULO, MultiplicativeType::MODULO}
    };

    const std::unordered_map<TokenType, ConstantType> typeNames = {
            {TokenType::INT_KEYWORD, ConstantType::INTEGER},
            {TokenType::FLOAT_KEYWORD, ConstantType::FLOAT},
            {TokenType::STRING_KEYWORD, ConstantType::STRING}
    };

    const std::unordered_map<TokenType, ConstantType> constantTypes = {
            {TokenType::INTEGER_VALUE, ConstantType::INTEGER},
            {TokenType::FLOAT_VALUE, ConstantType::FLOAT},
            {TokenType::STRING_LITERAL, ConstantType::STRING}
    };
}

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
    errorHandler(currentToken->getPosition(), type);
    throw std::exception();
}

/*
 * program = {instruction}
 */
Program MyLangParser::parse() {
    std::vector<InstructionPtr> instructions;
    while (parseInstruction(instructions));

    Program program(std::move(instructions));
    return program;
}

/*
 * instruction = block | single_instruction | statement
 */
bool MyLangParser::parseInstruction(std::vector<InstructionPtr>& instructions) {
    InstructionPtr instruction = parseBlock();
    if (!instruction)
        instruction = parseSingleInstruction();
    if (!instruction)
        instruction = parseStatement();
    if (instruction) {
        instructions.emplace_back(std::move(instruction));
        return true;
    }
    return false;
}

/*
 * block = ”{”, {instruction}, ”}”
 */
MyLangParser::BlockPtr MyLangParser::parseBlock() {
    std::vector<InstructionPtr> instructions;
    if (consumeIf(TokenType::LEFT_PARENTHESIS)) {
        while (parseInstruction(instructions));
        if (!consumeIf(TokenType::RIGHT_PARENTHESIS))
            criticalError(ErrorType::MISSING_PARENTHESIS);
        return std::make_unique<Block>(std::move(instructions));
    }
    return {};
}

/*
 * single_instruction = (function_declaration | variable_declaration | assign_or_function_call)
 */
MyLangParser::SingleInstructionPtr MyLangParser::parseSingleInstruction() {
    SingleInstructionPtr instruction = parseFunctionDeclaration();
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
MyLangParser::StatementPtr MyLangParser::parseStatement() {
    StatementPtr instruction = parseIfStatement();
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
MyLangParser::SingleInstructionPtr MyLangParser::parseVariableDeclarationOrAssignOrFunctionCall() {
    bool mut = false;
    if (consumeIf(TokenType::MUT_KEYWORD))
        mut = true;
    IdentifierPtr identifier = parseIdentifier();
    if (!identifier) {
        if (!mut)
            return {};
        criticalError(ErrorType::MUT_OUTSIDE_DECLARATION);
    }
    SingleInstructionPtr functionCall = parseFunctionCall(identifier->getName());
    if (functionCall) {
        if (!consumeIf(TokenType::SEMICOLON))
            errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
        return functionCall;
    }
    if (!consumeIf(TokenType::ASSIGN)) {
        if (!consumeIf(TokenType::SEMICOLON))
            errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
        return std::make_unique<VariableDeclaration>(std::move(identifier), mut);
    }
    ExpressionPtr expression = parseExpressionOrPair();
    if (!expression) {
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    }
    if (!consumeIf(TokenType::SEMICOLON))
        errorHandler(currentToken->getPosition(), ErrorType::MISSING_SEMICOLON);
    if (mut)
        return std::make_unique<VariableDeclaration>(VariableDeclaration(std::move(identifier),
                                                                         std::move(expression), mut));
    return std::make_unique<Assign>(std::move(identifier),std::move(expression));
}

/*
 * expression = and_expression, {"||”, and_expression}
 * pair = expression, expression
 */
MyLangParser::ExpressionPtr MyLangParser::parseExpressionOrPair() {
    ExpressionPtr first = parseExpression();
    if (!first)
        return {};
    if (!consumeIf(TokenType::COMMA))
        return first;
    ExpressionPtr second = parseExpression();
    if (!second)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    return std::make_unique<Pair>(std::move(first), std::move(second));
}

/*
 * function_declaration	= ”func”, identifier, arguments_list, block
 */
MyLangParser::SingleInstructionPtr
MyLangParser::parseFunctionDeclaration() {
    if (!consumeIf(TokenType::FUNC_KEYWORD))
        return {};
    Position position = currentToken->getPosition();
    IdentifierPtr identifier = parseIdentifier();
    if (!identifier)
        criticalError(ErrorType::IDENTIFIER_EXPECTED);
    std::optional<std::vector<Argument>> args = parseArgumentsList();
    if (!args)
        criticalError(ErrorType::ARGUMENTS_LIST_EXPECTED);
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<FunctionDeclaration>(position, identifier->getName(),
            std::move(block), std::move(args.value()));
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
    IdentifierPtr identifier = parseIdentifier();
    if (!identifier) {
        if (ref)
            criticalError(ErrorType::IDENTIFIER_EXPECTED);
        return {};
    }
    return Argument(currentToken->getPosition(), identifier->getName(), ref);
}

/*
 * function_call = "(", [expression, {",", expression}], ”)”
 */
MyLangParser::FunctionCallPtr MyLangParser::parseFunctionCall(const std::string& identifier) {
    if (!consumeIf(TokenType::LEFT_BRACKET))
        return {};
    ExpressionPtr firstArgument = parseExpression();
    if (!firstArgument) {
        if (!consumeIf(TokenType::RIGHT_BRACKET))
            criticalError(ErrorType::BRACKET_EXPECTED);
        return std::make_unique<FunctionCall>(
                Identifier(currentToken->getPosition(), identifier), std::vector<ExpressionPtr>());
    }
    std::vector<ExpressionPtr> args;
    args.emplace_back(std::move(firstArgument));
    while (consumeIf(TokenType::COMMA)) {
        ExpressionPtr arg = parseExpression();
        if (!arg)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        args.emplace_back(std::move(arg));
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
MyLangParser::StatementPtr MyLangParser::parseIfStatement() {
    if (!consumeIf(TokenType::IF_KEYWORD))
        return {};
    ExpressionPtr expression = parseExpression();
    if (!expression)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    BlockPtr ifBlock = parseBlock();
    if (!ifBlock)
        criticalError(ErrorType::BLOCK_EXPECTED);
    BlockPtr elseBlock = parseElseStatement();
    return std::make_unique<IfStatement>(std::move(expression),
                                         std::move(ifBlock), std::move(elseBlock));
}

/*
 * else_statement = "else”, block
 */
MyLangParser::BlockPtr MyLangParser::parseElseStatement() {
    if (!consumeIf(TokenType::ELSE_KEYWORD))
        return {};
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return block;
}

/*
 * loop_statement = "loop”, expression, block
 */
MyLangParser::StatementPtr MyLangParser::parseLoopStatement() {
    if (!consumeIf(TokenType::LOOP_KEYWORD))
        return {};
    ExpressionPtr expression = parseExpression();
    if (!expression)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<LoopStatement>(std::move(expression), std::move(block));
}

/*
 * pattern_statement = "pattern”, expression, "{", {match_statement}, ”}”
 */
MyLangParser::StatementPtr MyLangParser::parsePatternStatement() {
    if (!consumeIf(TokenType::PATTERN_KEYWORD))
        return {};
    ExpressionPtr expression = parseExpression();
    if (!expression)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    if (!consumeIf(TokenType::LEFT_PARENTHESIS))
        criticalError(ErrorType::MISSING_PARENTHESIS);
    std::vector<MatchStatement::MatchStatementPtr> matches;
    while (parseMatchStatement(matches));
    if (!consumeIf(TokenType::RIGHT_PARENTHESIS))
        criticalError(ErrorType::MISSING_PARENTHESIS);
    return std::make_unique<PatternStatement>(std::move(expression), std::move(matches));
}

/*
 * match_statement = "match", (match_expression | match_pair | match_string | match_float | match_int | match_none)
 */
bool MyLangParser::parseMatchStatement(std::vector<MatchStatement::MatchStatementPtr>& matches) {
    if (!consumeIf(TokenType::MATCH_KEYWORD))
        return false;
    MatchStatementPtr statement = parseMatchType();
    if (!statement)
        statement = parseMatchNone();
    if (!statement)
        statement = parseMatchPairOrExpression();
    if (!statement)
        criticalError(ErrorType::INVALID_MATCH_SYNTAX);
    matches.emplace_back(std::move(statement));
    return true;
}

/*
 * match_string	= "String”, ”(”, identifier, ”)”, block
 * match_float  = "Float”, ”(”, identifier, ”)”, block
 * match_int	= "Int”, ”(”, identifier, ”)”, block
 */
MyLangParser::MatchStatementPtr MyLangParser::parseMatchType() {
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
    IdentifierPtr identifier = parseIdentifier();
    if (!identifier)
        criticalError(ErrorType::IDENTIFIER_EXPECTED);
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchType>(std::move(block), std::move(identifier), type);
}

/*
 * match_none = "none", block
 */
MyLangParser::MatchStatementPtr MyLangParser::parseMatchNone() {
    if (!consumeIf(TokenType::NONE_KEYWORD))
        return {};
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchNone>(std::move(block));
}

/*
 * match_expression		= expression, ”(”, identifier, ”)”, block
 * match_pair			= pair, block
 */
MyLangParser::MatchStatementPtr MyLangParser::parseMatchPairOrExpression() {
    ExpressionPtr expression = parseExpression();
    if (!expression)
        return {};
    if (consumeIf(TokenType::COMMA))
        return parseMatchPair(std::move(expression));
    return parseMatchExpression(std::move(expression));
}

/*
 * match_pair = expression, ",”, expression, block
 */
MyLangParser::MatchStatementPtr MyLangParser::parseMatchPair(MyLangParser::ExpressionPtr first) {
    ExpressionPtr second = parseExpression();
    if (!second)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchPair>(std::move(block), std::move(first),std::move(second));
}

/*
 * match_expression	= expression, ”(”, identifier, ”)”, block
 */
MyLangParser::MatchStatementPtr MyLangParser::parseMatchExpression(MyLangParser::ExpressionPtr expression) {
    if (!consumeIf(TokenType::LEFT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    IdentifierPtr identifier = parseIdentifier();
    if (!identifier)
        criticalError(ErrorType::IDENTIFIER_EXPECTED);
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    BlockPtr block = parseBlock();
    if (!block)
        criticalError(ErrorType::BLOCK_EXPECTED);
    return std::make_unique<MatchExpression>(std::move(expression), std::move(identifier),
                                             std::move(block));
}

/*
 * return_statement	= ”return”, [expression], ”;”
 */
MyLangParser::StatementPtr MyLangParser::parseReturnStatement() {
    if (!consumeIf(TokenType::RETURN_KEYWORD))
        return {};
    ExpressionPtr expression = parseExpression();
    if (!consumeIf(TokenType::SEMICOLON))
        criticalError(ErrorType::MISSING_SEMICOLON);
    if (expression)
        return std::make_unique<ReturnStatement>(std::move(expression));
    return std::make_unique<ReturnStatement>();
}

/*
 * expression = and_expression, {"||”, and_expression}
 */
MyLangParser::ExpressionPtr MyLangParser::parseExpression() {
    ExpressionPtr left = parseAndExpression();
    if (!left)
        return {};
    while (consumeIf(TokenType::OR)) {
        ExpressionPtr right = parseAndExpression();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<OrExpression>(currentToken->getPosition(), std::move(left),
                                              std::move(right));
    }
    return left;
}

/*
 * and_expression = relative_expression, {"&&”, relative_expression}
 */
MyLangParser::ExpressionPtr MyLangParser::parseAndExpression() {
    ExpressionPtr left = parseRelativeExpression();
    if (!left)
        return {};
    while (consumeIf(TokenType::AND)) {
        ExpressionPtr right = parseRelativeExpression();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<AndExpression>(currentToken->getPosition(), std::move(left),
                                              std::move(right));
    }
    return left;
}

/*
 * relative_expression = (numeric_expression, {operator, numeric_expression}) | is_expression
 * is_expression       = numeric_expression, {”is”, numeric_expression}
 */
MyLangParser::ExpressionPtr MyLangParser::parseRelativeExpression() {
    ExpressionPtr left = parseNumericExpression();
    if (!left)
        return {};
    auto it = relativeTypes.find(currentToken->getType());
    while (it != relativeTypes.end()) {
        nextToken();
        ExpressionPtr right = it->second == RelativeType::IS
                                      ? parseNumericPair() : parseNumericExpression();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<RelativeExpression>(currentToken->getPosition(), std::move(left),
                                                    std::move(right), it->second);
        it = relativeTypes.find(currentToken->getType());
    }
    return left;
}

/*
 * numeric_expression = term, {("+” | "-”), term }
 */
MyLangParser::ExpressionPtr MyLangParser::parseNumericExpression() {
    ExpressionPtr left = parseTerm();
    if (!left)
        return {};
    auto it = additiveTypes.find(currentToken->getType());
    while (it != additiveTypes.end()) {
        nextToken();
        ExpressionPtr right = parseTerm();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<AdditiveExpression>(currentToken->getPosition(), std::move(left),
                                                    std::move(right), it->second);
        it = additiveTypes.find(currentToken->getType());
    }
    return left;
}

/*
 * numeric_pair	= numeric_expression, ",", numeric_expression
 */
MyLangParser::ExpressionPtr MyLangParser::parseNumericPair() {
    ExpressionPtr first = parseNumericExpression();
    if (!first)
        return {};
    if (!consumeIf(TokenType::COMMA))
        return first;
    ExpressionPtr second = parseExpression();
    if (!second)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    return std::make_unique<Pair>(std::move(first), std::move(second));
}

/*
 * term	= factor, {("*” | "/” | "//” | "%”), factor};
 */
MyLangParser::ExpressionPtr MyLangParser::parseTerm() {
    ExpressionPtr left = parseFactor();
    if (!left)
        return {};
    auto it = multiplicativeTypes.find(currentToken->getType());
    while (it != multiplicativeTypes.end()) {
        nextToken();
        ExpressionPtr right = parseFactor();
        if (!right)
            criticalError(ErrorType::EXPRESSION_EXPECTED);
        left = std::make_unique<MultiplicationExpression>(currentToken->getPosition(), std::move(left),
                                                    std::move(right), it->second);
        it = multiplicativeTypes.find(currentToken->getType());
    }
    return left;
}

/*
 * factor = ["!" |"-"], constant | typename | id_or_function_call | field | cast_or_nested
 */
MyLangParser::ExpressionPtr MyLangParser::parseFactor() {
    bool negated = false;
    if (consumeIf(TokenType::NEGATION) || consumeIf(TokenType::MINUS))
        negated = true;
    ExpressionPtr expression = parseConstant();
    if (!expression)
        expression = parseIdentifierOrFunctionCall();
    if (!expression)
        expression = parseTypenameOrCastOrNestedExpression();
    if (!expression && negated)
        criticalError(ErrorType::EXPRESSION_EXPECTED);
    if (negated)
        return std::make_unique<NegatedExpression>(std::move(expression));
    return expression;
}

/*
 * constant	= number | string
 * number	= int | float
 */
MyLangParser::ExpressionPtr MyLangParser::parseConstant() {
    auto it = constantTypes.find(currentToken->getType());
    if (it == constantTypes.end())
        return {};
    if (it->second == ConstantType::INTEGER) {
        int value = std::get<int>(currentToken->getValue());
        nextToken();
        return std::make_unique<Constant>(currentToken->getPosition(), value);
    }
    if (it->second == ConstantType::FLOAT) {
        double value = std::get<double>(currentToken->getValue());
        nextToken();
        return std::make_unique<Constant>(currentToken->getPosition(), value);
    }
    if (it->second == ConstantType::STRING) {
        std::string value = std::get<std::string>(currentToken->getValue());
        nextToken();
        return std::make_unique<Constant>(currentToken->getPosition(), value);
    }
    return {};
}

/*
 * id_or_function_call = identifier, [function_call]
 * field = id_or_function_call, ”.”, ”first” | ”second”
 */
MyLangParser::ExpressionPtr MyLangParser::parseIdentifierOrFunctionCall() {
    ExpressionPtr expression;
    IdentifierPtr identifier = parseIdentifier();
    if (!identifier)
        return {};
    ExpressionPtr functionCall = std::move(parseFunctionCall(identifier->getName()));
    if (!functionCall)
        expression = std::move(identifier);
    else
        expression = std::move(functionCall);
    ExpressionPtr field = parseField(expression);
    if (!field)
        return expression;
    return field;
}

/*
 * field = id_or_function_call, ”.”, ”first” | ”second”
 */
MyLangParser::ExpressionPtr MyLangParser::parseField(ExpressionPtr& expression) {
    Position position = currentToken->getPosition();
    if (!consumeIf(TokenType::DOT))
        return {};
    if (currentToken->getType() == TokenType::IDENTIFIER
                                && std::get<std::string>(currentToken->getValue()) == "first") {
        nextToken();
        return std::make_unique<Field>(position, std::move(expression), FieldType::FIRST);
    }
    if (currentToken->getType() == TokenType::IDENTIFIER
                                && std::get<std::string>(currentToken->getValue()) == "second") {
        nextToken();
        return std::make_unique<Field>(position, std::move(expression), FieldType::SECOND);
    }
    criticalError(ErrorType::FIRST_OR_SECOND_EXPECTED);
    return {};
}

/*
 * identifier = (letter | ”_”), {letter | digit | ”_”}
 */
MyLangParser::IdentifierPtr MyLangParser::parseIdentifier() {
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
MyLangParser::ExpressionPtr MyLangParser::parseTypenameOrCastOrNestedExpression() {
    Position position = currentToken->getPosition();
    auto it = typeNames.find(currentToken->getType());
    if (it != typeNames.end())
        nextToken();
    if (!consumeIf(TokenType::LEFT_BRACKET)) {
        if (it != typeNames.end())
            return std::make_unique<Typename>(position, it->second);
        else
            return {};
    }
    ExpressionPtr expression = parseExpression();
    if (!consumeIf(TokenType::RIGHT_BRACKET))
        criticalError(ErrorType::BRACKET_EXPECTED);
    if (it != typeNames.end())
        return std::make_unique<CastExpression>(position, std::move(expression), it->second);
    return expression;
}
