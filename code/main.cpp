#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

#include "LexerWithoutComments.h"
#include "print_utils.h"

void onLexerError(Position position, ErrorType error) {
    std::cout << "Error: ";
    using PrintUtils::toString;
    std::cout << toString(error) <<"\n\t";
    std::cout << "line: " << position.getLine() << ' ';
    std::cout << "column: " << position.getColumn() << '\n';
}

void printTokens(Lexer* lexer, int maxTokenCount = 4096) {
    Token token;
    std::cout.precision(10);
    while (maxTokenCount--) {
        if (!lexer->nextToken())
            continue;
        token = lexer->getToken();
        if (token.getType() == TokenType::END_OF_TEXT)
            return;
        std::cout << "line: " << token.getPosition().getLine() << ' ';
        std::cout << "column: " << token.getPosition().getColumn() << ' ';
        switch (token.getType()) {
            case TokenType::INTEGER_VALUE:
                std::cout << "int value: " << std::get<int>(token.getValue()) << '\n';
                break;
            case TokenType::FLOAT_VALUE:
                std::cout << "float value: " << std::get<double>(token.getValue()) << '\n';
                break;
            case TokenType::STRING_LITERAL:
                std::cout << "string literal: " << std::get<std::string>(token.getValue()) << '\n';
                break;
            case TokenType::COMMENT:
                std::cout << "comment: " << std::get<std::string>(token.getValue()) << '\n';
                break;
            case TokenType::IDENTIFIER:
                std::cout << "identifier: " << std::get<std::string>(token.getValue()) << '\n';
                break;
            default:
                using PrintUtils::toString;
                std::cout << "operator or keyword: " << toString(token.getType()) << '\n';
                break;
        }
    }
    if (!maxTokenCount) {
        std::cout << "reached maxTokenCount\n";
    }
}

int main(int argc, char** argv) {
    bool dontIgnoreComments = false;
    if (argc > 2) {
        dontIgnoreComments = !strcmp(argv[2], "--dont-ignore-comments");
    }
    if (argc > 1) {
        std::ifstream fin(argv[1]);
        if (dontIgnoreComments) {
            MyLangLexer myLangLexer(fin, onLexerError);
            printTokens(&myLangLexer);
        } else {
            LexerWithoutComments lexerWithoutComments(fin, onLexerError);
            printTokens(&lexerWithoutComments);
        }
        fin.close();
    } else {
        std::cout << "USAGE: " << argv[0] << " <input file> [--dont-ignore-comments]\n";
    }

    return 0;
}