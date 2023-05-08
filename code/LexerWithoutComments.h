
#ifndef CODE_LEXERWITHOUTCOMMENTS_H
#define CODE_LEXERWITHOUTCOMMENTS_H

#include "MyLangLexer.h"

class LexerWithoutComments : public Lexer {
    MyLangLexer myLangLexer;
public:
    LexerWithoutComments(std::istream&, HandlerType);

    std::optional<Token> nextToken() override;
};


#endif //CODE_LEXERWITHOUTCOMMENTS_H
