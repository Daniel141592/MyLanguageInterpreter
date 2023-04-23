
#ifndef CODE_LEXERWITHOUTCOMMENTS_H
#define CODE_LEXERWITHOUTCOMMENTS_H

#include "MyLangLexer.h"

class LexerWithoutComments : public Lexer {
    MyLangLexer myLangLexer;
public:
    LexerWithoutComments(std::istream&, HandlerType);

    bool nextToken() override;
    Token getToken() const override;
};


#endif //CODE_LEXERWITHOUTCOMMENTS_H
