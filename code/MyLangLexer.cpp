#include "MyLangLexer.h"
#include "ErrorType.h"

std::map<std::string, TokenType> MyLangLexer::keywords;
std::map<char, char> MyLangLexer::specialChars;
std::map<char, TokenType> MyLangLexer::simpleTokens;
std::map<std::string, TokenType> MyLangLexer::twoCharactersTokens;

void MyLangLexer::initializeKeywordsAndSpecialChars() {
    keywords = {
            {"mut", TokenType::MUT},
            {"Int", TokenType::INT_KEYWORD},
            {"Float", TokenType::FLOAT_KEYWORD},
            {"String", TokenType::STRING_KEYWORD},
            {"loop", TokenType::LOOP},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"pattern", TokenType::PATTERN},
            {"match", TokenType::MATCH},
            {"is", TokenType::IS},
            {"func", TokenType::FUNC_KEYWORD},
            {"none", TokenType::NONE_KEYWORD},
            {"ref", TokenType::REF_KEYWORD}
    };

    specialChars = {
            {'b', 8}, {'f', 12}, {'n', 10},
            {'r', 13}, {'t', 9}, {'"', '"'},
            {'\\', '\\'}
    };

    simpleTokens = {
            {'(', TokenType::LEFT_BRACKET}, {')', TokenType::RIGHT_BRACKET},
            {'{', TokenType::LEFT_PARENTHESIS}, {'}', TokenType::RIGHT_PARENTHESIS},
            {';', TokenType::SEMICOLON}, {',', TokenType::COMMA},
            {'.', TokenType::DOT}, {'=', TokenType::ASSIGN},
            {'>', TokenType::GREATER_THAN}, {'<', TokenType::LESS_THAN},
            {'!', TokenType::NEGATION}, {'%', TokenType::MODULO},
            {'+', TokenType::PLUS}, {'-', TokenType::MINUS},
            {'*', TokenType::ASTERISK}, {'/', TokenType::DIVISION}
    };

    twoCharactersTokens = {
            {">=", TokenType::GREATER_OR_EQUAL}, {"<=", TokenType::LESS_OR_EQUAL},
            {"==", TokenType::EQUAL}, {"//", TokenType::INT_DIVISION}
    };
}

MyLangLexer::MyLangLexer(std::istream &i, HandlerType error) : is(i), errorHandler(std::move(error)) {
    MyLangLexer::initializeKeywordsAndSpecialChars();
    i.get(ch);
}

Token MyLangLexer::getToken() const {
    return token;
}

bool MyLangLexer::nextCharacter() {
    if (ch == '\n') {       //TODO ogarnąć inne sekwencje końca linii
        position.setColumn(1);
        position.addLine();
    } else
        position.addColumn();
    is.get(ch);
    if (is.eof())
        return false;
    return true;
}

bool MyLangLexer::nextToken() {
    while (isspace(ch) && nextCharacter());
    if (is.eof()) {
        token = Token(TokenType::END_OF_TEXT, position);
        return true;
    }
    if (tryBuildSimpleTokens()  //TODO rozważyć migrację na std::optional
        || tryBuildNumber()
        || tryBuildIdentifierOrKeyword()
        || tryBuildComment()
        || tryBuildString()) {
            return true;
    }
    errorHandler(position, ErrorType::UnknownToken);
    nextCharacter();
    return false;
}

bool MyLangLexer::tryBuildSimpleTokens() {
    if (!simpleTokens.count(ch))
        return false;
    Position tokenPosition = position;
    if (ch == '=' || ch == '>' || ch == '<' || ch == '/') {
        char first = ch;
        if (!nextCharacter()) {
            token = Token(simpleTokens[ch], tokenPosition);
        } else {
            std::string str = std::string() + first + ch;
            if (twoCharactersTokens.count(str)) {
                token = Token(twoCharactersTokens[str], tokenPosition);
                nextCharacter();
            }
            else
                token = Token(simpleTokens[first], tokenPosition);
        }
    } else {
        token = Token(simpleTokens[ch], tokenPosition);
        nextCharacter();
    }
    return true;
}

bool MyLangLexer::tryBuildNumber() {
    if (!isdigit(ch))
        return false;
    int value = ch - '0';
    Position tokenPosition = position;
    nextCharacter();
    if (value != 0) {
        while (isdigit(ch)) {
            int decimal = ch - '0';
            if ((INTMAX_MAX - decimal) / 10 > value)
                value = value * 10 + decimal;
            else
                errorHandler(tokenPosition, ErrorType::IntRangeError);
            if (!nextCharacter()) {
                token = Token(TokenType::INTEGER_VALUE, value, tokenPosition);
                return true;
            }
        }
    }
    if (ch == '.') {
        nextCharacter();
        int numOfDecimals = 0;
        int fraction = 0;
        while (isdigit(ch)) {
            ++numOfDecimals;
            int decimal = ch - '0';
            if ((INTMAX_MAX - decimal) / 10 > fraction)
                fraction = fraction * 10 + decimal;
            else
                errorHandler(tokenPosition, ErrorType::IntRangeError);
            if (!nextCharacter()) {
                token = Token(TokenType::FLOAT_VALUE, value + fraction / pow(10, numOfDecimals), tokenPosition);
                return true;
            }
        }
        if (!numOfDecimals)
            errorHandler(tokenPosition, ErrorType::IncorrectFloatValue);

        double floatValue = value + fraction / pow(10, numOfDecimals);
        token = Token(TokenType::FLOAT_VALUE, floatValue, tokenPosition);
    } else
        token = Token(TokenType::INTEGER_VALUE, value, tokenPosition);
    return true;
}

bool MyLangLexer::tryBuildIdentifierOrKeyword() {
    if (!isalpha(ch) && ch != '_')
        return false;
    Position tokenPosition = position;
    std::string str;
    int size = 0;

    while (isalpha(ch) || isdigit(ch) || ch == '_') {
        str += ch;
        if (!nextCharacter()) {
            errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
            break;
        }
        if (size++ >= MAX_IDENTIFIER_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongIdentifier);
            break;
        }
    }

    if (keywords.count(str))
        token = Token(keywords[str], tokenPosition);
    else
        token = Token(TokenType::IDENTIFIER, str, tokenPosition);
    return true;
}

bool MyLangLexer::tryBuildComment() {
    if (ch != '$')
        return false;
    Position tokenPosition = position;
    std::string str;
    int size = 0;
    nextCharacter();
    while (ch != '\n') {
        str += ch;
        if (size++ >= MAX_COMMENT_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongComment);
            break;
        }
        if (!nextCharacter())
            break;
    }
    token = Token(TokenType::COMMENT, str, tokenPosition);
    return true;
}

bool MyLangLexer::tryBuildString() {
    if (ch != '"')
        return false;
    Position tokenPosition = position;
    if (!nextCharacter()) {
        errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
    }

    std::string str;
    int size = 0;
    while (ch != '"') {
        if (ch == '\\') {
            if (!nextCharacter()) {
                errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
                break;
            }
            if (!specialChars.count(ch)) {
                errorHandler(position, ErrorType::UnknownEscapeCharacter);
            } else {
                str += specialChars[ch];
            }
        } else {
            str += ch;
        }
        if (!nextCharacter()) {
            errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
            break;
        }
        if (size++ >= MAX_STRING_LITERAL_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongStringLiteral);
            break;
        }
    }

    token = Token(TokenType::STRING_LITERAL, str, tokenPosition);
    if (ch == '"')
        nextCharacter();
    return true;
}
