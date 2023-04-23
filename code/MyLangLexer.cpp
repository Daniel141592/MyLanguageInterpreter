#include "MyLangLexer.h"

std::unordered_map<std::string, TokenType> MyLangLexer::keywords;
std::unordered_map<char, char> MyLangLexer::specialChars;
std::unordered_map<char, TokenType> MyLangLexer::simpleTokens;
std::unordered_map<std::string, TokenType> MyLangLexer::twoCharactersTokens;

void MyLangLexer::initializeKeywordsAndSpecialChars() {
    keywords = {
            {"mut", TokenType::MUT_KEYWORD},
            {"Int", TokenType::INT_KEYWORD},
            {"Float", TokenType::FLOAT_KEYWORD},
            {"String", TokenType::STRING_KEYWORD},
            {"loop", TokenType::LOOP_KEYWORD},
            {"if", TokenType::IF_KEYWORD},
            {"else", TokenType::ELSE_KEYWORD},
            {"pattern", TokenType::PATTERN_KEYWORD},
            {"match", TokenType::MATCH_KEYWORD},
            {"is", TokenType::IS_KEYWORD},
            {"func", TokenType::FUNC_KEYWORD},
            {"none", TokenType::NONE_KEYWORD},
            {"ref", TokenType::REF_KEYWORD},
            {"return", TokenType::RETURN_KEYWORD}
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
            {"==", TokenType::EQUAL}, {"!=", TokenType::NOT_EQUAL},
            {"//", TokenType::INT_DIVISION}
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
        errorHandler(position, ErrorType::InconsistentNewlineSequence);
        return true;
    }
    if (currentChar == '\r' || currentChar == '\n') {
        errorHandler(position, ErrorType::InconsistentNewlineSequence);
        is.get(currentChar);
        return true;
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
    std::optional<Token> result = tryBuildSimpleTokens();
    result = result ? result : tryBuildNumber();
    result = result ? result : tryBuildIdentifierOrKeyword();
    result = result ? result : tryBuildComment();
    result = result ? result : tryBuildString();
    if (result) {
        token = *result;
        return true;
    }
    errorHandler(position, ErrorType::UnknownToken);
    nextCharacter();
    return false;
}

std::optional<Token> MyLangLexer::tryBuildSimpleTokens() {
    if (!simpleTokens.count(currentChar))
        return {};
    Position tokenPosition = position;
    if (currentChar == '=' || currentChar == '>' || currentChar == '<' || currentChar == '/' || currentChar == '!') {
        char first = currentChar;
        if (!nextCharacter()) {
            return Token(simpleTokens[currentChar], tokenPosition);
        }
        std::string str = std::string() + first + currentChar;
        if (twoCharactersTokens.count(str)) {
            nextCharacter();
            return Token(twoCharactersTokens[str], tokenPosition);
        }
        return Token(simpleTokens[first], tokenPosition);
    }
    char value = currentChar;
    nextCharacter();
    return Token(simpleTokens[value], tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildNumber() {
    if (!isdigit(currentChar))
        return {};
    int value = currentChar - '0';
    Position tokenPosition = position;
    nextCharacter();
    if (value != 0) {
        while (isdigit(currentChar)) {
            int decimal = currentChar - '0';
            if ((INT_MAX - decimal) / 10 - value > 0)
                value = value * 10 + decimal;
            else
                errorHandler(tokenPosition, ErrorType::IntRangeError);
            if (!nextCharacter()) {
                return Token(TokenType::INTEGER_VALUE, value, tokenPosition);
            }
        }
    }
    if (currentChar == '.') {
        if (!nextCharacter())
            errorHandler(tokenPosition, ErrorType::IncorrectFloatValue);
        int numOfDecimals = 0;
        int fraction = 0;
        while (isdigit(currentChar)) {
            ++numOfDecimals;
            int decimal = currentChar - '0';
            if ((INT_MAX - decimal) / 10 > fraction)
                fraction = fraction * 10 + decimal;
            else
                errorHandler(tokenPosition, ErrorType::IntRangeError);
            if (!nextCharacter()) {
                return Token(TokenType::FLOAT_VALUE, value + fraction / pow(10, numOfDecimals), tokenPosition);
            }
        }
        double floatValue = value + fraction / pow(10, numOfDecimals);
        return Token(TokenType::FLOAT_VALUE, floatValue, tokenPosition);
    }
    return Token(TokenType::INTEGER_VALUE, value, tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildIdentifierOrKeyword() {
    if (!isalpha(currentChar) && currentChar != '_')
        return {};
    Position tokenPosition = position;
    std::string str;
    int size = 0;

    while (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_') {
        str += currentChar;
        if (!nextCharacter())
            break;
        if (++size >= MAX_IDENTIFIER_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongIdentifier);
            break;
        }
    }

    if (keywords.count(str))
        return Token(keywords[str], tokenPosition);
    return Token(TokenType::IDENTIFIER, str, tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildComment() {
    if (currentChar != '$')
        return {};
    Position tokenPosition = position;
    std::string str;
    int size = 0;
    nextCharacter();
    while (currentChar != '\n' && currentChar != '\r') {
        str += currentChar;
        if (++size >= MAX_COMMENT_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongComment);
            break;
        }
        if (!nextCharacter())
            break;
    }
    return Token(TokenType::COMMENT, str, tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildString() {
    if (currentChar != '"')
        return {};
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
        if (++size >= MAX_STRING_LITERAL_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongStringLiteral);
            break;
        }
    }
    if (currentChar == '"')
        nextCharacter();
    return Token(TokenType::STRING_LITERAL, str, tokenPosition);
}
