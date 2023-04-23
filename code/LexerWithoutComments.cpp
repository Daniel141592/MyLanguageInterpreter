#include "LexerWithoutComments.h"

LexerWithoutComments::LexerWithoutComments(std::istream& is, HandlerType onError)
                    : myLangLexer(std::move(MyLangLexer(is, std::move(onError)))){
}

Token LexerWithoutComments::getToken() const {
    return myLangLexer.getToken();
}

bool LexerWithoutComments::nextToken() {
    do {
        if (!myLangLexer.nextToken())
            return false;
    } while (myLangLexer.getToken().getType() == TokenType::COMMENT);
    return true;
}
