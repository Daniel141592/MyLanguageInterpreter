#include <iostream>
#include <sstream>
#include <fstream>
#include "MyLangLexer.h"

void onLexerError(Position position, ErrorType error) {
    std::cout << "Error: ";
    switch (error) {
        case IntRangeError:
            std::cout << "IntRangeError";
            break;
        case IncorrectFloatValue:
            std::cout << "IncorrectFloatValue";
            break;
        case UnknownToken:
            std::cout << "UnknownToken";
            break;
        case UnexpectedEndOfText:
            std::cout << "UnexpectedEndOfText";
            break;
        case UnknownEscapeCharacter:
            std::cout << "UnknownEscapeCharacter";
            break;
        case TooLongStringLiteral:
            std::cout << "TooLongStringLiteral";
            break;
        case TooLongIdentifier:
            std::cout << "TooLongIdentifier";
            break;
        case TooLongComment:
            std::cout << "TooLongComment";
            break;
        case OtherError:
            std::cout << "OtherError";
            break;
    }
    std::cout <<"\n\t";
    std::cout << "line: " << position.getLine() << ' ';
    std::cout << "column: " << position.getColumn() << '\n';
}

void printTokens(std::istream& istream, int maxTokenCount = 4096) {
    MyLangLexer lexer(istream, onLexerError);
    Token token;
    std::cout.precision(10);
    while (maxTokenCount--) {
        if (!lexer.nextToken())
            continue;
        token = lexer.getToken();
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
                std::cout << "operator or keyword" << '\n'; //TODO spróbować wyświetlić typ dokładniej
                break;
        }
    }
    if (!maxTokenCount) {
        std::cout << "reached maxTokenCount\n";
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        std::ifstream fin(argv[1]);
        printTokens(fin);
        fin.close();
    } else {
        std::string test = "<<=1.12345678 420.069 loop if nazwa_zmiennej 2137$papież XD\n\"test\\\\backslash\"   \n\"cytat \\\"lubie piwo\\\"\"$chu1";
        std::istringstream iss(test);
        printTokens(iss);
    }

    return 0;
}
