#ifndef CODE_MYLANGPARSER_H
#define CODE_MYLANGPARSER_H

#include "Parser.h"

class MyLangParser : public Parser {
    using InstructionPtr = Instruction::InstructionPtr;
    std::unique_ptr<Lexer> lexer;
    HandlerType errorHandler;
    Token currentToken;
    Token previousToken;
public:
    MyLangParser(std::unique_ptr<Lexer> l, HandlerType onError);
    Program parse() override;
private:
    void nextToken();
};


#endif //CODE_MYLANGPARSER_H
