#include "LexerWithoutComments.h"

LexerWithoutComments::LexerWithoutComments(std::istream& is, HandlerType onError)
                    : myLangLexer(std::move(MyLangLexer(is, std::move(onError)))){
}

std::optional<Token> LexerWithoutComments::nextToken() {
    std::optional<Token> token;
    do {
        token = myLangLexer.nextToken();
        if (!token)
            return {};
    } while (token->getType() == TokenType::COMMENT);
    return token;
}
