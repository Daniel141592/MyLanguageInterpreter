#include "MyLangParser.h"

MyLangParser::MyLangParser(std::unique_ptr<Lexer> l, Parser::HandlerType onError) : lexer(std::move(l)), errorHandler(std::move(onError)) {
    currentToken = lexer->nextToken().value();
}

/*
 * program = instruction, {instruction}
 *
 */
Program MyLangParser::parse() {
    std::vector<InstructionPtr> instructions;

    Program program(std::move(instructions));
    return program;
}

void MyLangParser::nextToken() {
    previousToken = currentToken;
    auto tokenOptional = lexer->nextToken();
    if (tokenOptional)
        currentToken = tokenOptional.value();
}
