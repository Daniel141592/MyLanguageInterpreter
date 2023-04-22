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
            {"ref", TokenType::REF_KEYWORD},
            {"return", TokenType::RETURN}
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
    i.get(currentChar);
}

Token MyLangLexer::getToken() const {
    return token;
}

bool MyLangLexer::newLineSeqReached() {
    if (newLineSeq.size() == 1 && newLineSeq[0] == currentChar) {
        is.get(currentChar);
        if ((currentChar == '\r' || currentChar == '\n') && currentChar != newLineSeq[0]) {
            errorHandler(position, ErrorType::InconsistentNewlineSequence);
            is.get(currentChar);
        }
        return true;
    }
    if (newLineSeq.size() == 2 && newLineSeq[0] == currentChar) {
        is.get(currentChar);
        if (newLineSeq[1] == currentChar) {
            is.get(currentChar);
            return true;
        }
        return false;
    }
    is.get(currentChar);
    return false;
}

void MyLangLexer::trySetNewlineSeq() {
    if (currentChar == '\n' || currentChar == '\r') {
        newLineSeq += currentChar;
        position.setColumn(1);
        position.addLine();
        is.get(currentChar);
        if ((currentChar == '\r' || currentChar == '\n') && currentChar != newLineSeq[0]) {
            newLineSeq += currentChar;
            is.get(currentChar);
        }
        return;
    }
    position.addColumn();
    is.get(currentChar);
}

bool MyLangLexer::nextCharacter() {
    if (!newLineSeq.empty() && newLineSeqReached()) {
        position.setColumn(1);
        position.addLine();
    } else if (!newLineSeq.empty()) {
        position.addColumn();
    } else {
        trySetNewlineSeq();
    }
    if (is.eof())
        return false;
    return true;
}

bool MyLangLexer::nextToken() {
    while (isspace(currentChar) && nextCharacter());
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
    if (!simpleTokens.count(currentChar))
        return false;
    Position tokenPosition = position;
    if (currentChar == '=' || currentChar == '>' || currentChar == '<' || currentChar == '/') {
        char first = currentChar;
        if (!nextCharacter()) {
            token = Token(simpleTokens[currentChar], tokenPosition);
        } else {
            std::string str = std::string() + first + currentChar;
            if (twoCharactersTokens.count(str)) {
                token = Token(twoCharactersTokens[str], tokenPosition);
                nextCharacter();
            }
            else
                token = Token(simpleTokens[first], tokenPosition);
        }
    } else {
        token = Token(simpleTokens[currentChar], tokenPosition);
        nextCharacter();
    }
    return true;
}

bool MyLangLexer::tryBuildNumber() {
    if (!isdigit(currentChar))
        return false;
    int value = currentChar - '0';
    Position tokenPosition = position;
    nextCharacter();
    if (value != 0) {
        while (isdigit(currentChar)) {
            int decimal = currentChar - '0';
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
    if (currentChar == '.') {
        nextCharacter();
        int numOfDecimals = 0;
        int fraction = 0;
        while (isdigit(currentChar)) {
            ++numOfDecimals;
            int decimal = currentChar - '0';
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
    if (!isalpha(currentChar) && currentChar != '_')
        return false;
    Position tokenPosition = position;
    std::string str;
    int size = 0;

    while (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_') {
        str += currentChar;
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
    if (currentChar != '$')
        return false;
    Position tokenPosition = position;
    std::string str;
    int size = 0;
    nextCharacter();
    while (currentChar != '\n' && currentChar != '\r') {
        str += currentChar;
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
    if (currentChar != '"')
        return false;
    Position tokenPosition = position;
    if (!nextCharacter()) {
        errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
    }

    std::string str;
    int size = 0;
    while (currentChar != '"') {
        if (currentChar == '\\') {
            if (!nextCharacter()) {
                errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
                break;
            }
            if (!specialChars.count(currentChar)) {
                errorHandler(position, ErrorType::UnknownEscapeCharacter);
            } else {
                str += specialChars[currentChar];
            }
        } else {
            str += currentChar;
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
    if (currentChar == '"')
        nextCharacter();
    return true;
}
