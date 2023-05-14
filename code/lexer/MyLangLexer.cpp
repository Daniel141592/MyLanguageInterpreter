#include "MyLangLexer.h"

namespace {
    const char EOT = 0x04;
    const std::unordered_map<std::string, TokenType> keywords {
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
            {"return", TokenType::RETURN_KEYWORD},
            {"first", TokenType::FIRST_KEYWORD},
            {"second", TokenType::SECOND_KEYWORD}
    };
    const std::unordered_map<char, char> specialChars {
            {'b', 8}, {'f', 12}, {'n', 10},
            {'r', 13}, {'t', 9}, {'"', '"'},
            {'\\', '\\'}, {EOT, EOT}
    };
    const std::unordered_map<char, TokenType> simpleTokens {
            {'(', TokenType::LEFT_BRACKET}, {')', TokenType::RIGHT_BRACKET},
            {'{', TokenType::LEFT_PARENTHESIS}, {'}', TokenType::RIGHT_PARENTHESIS},
            {';', TokenType::SEMICOLON}, {',', TokenType::COMMA},
            {'.', TokenType::DOT}, {'=', TokenType::ASSIGN},
            {'>', TokenType::GREATER_THAN}, {'<', TokenType::LESS_THAN},
            {'!', TokenType::NEGATION}, {'%', TokenType::MODULO},
            {'+', TokenType::PLUS}, {'-', TokenType::MINUS},
            {'*', TokenType::ASTERISK}, {'/', TokenType::DIVISION}
    };
    const std::unordered_map<std::string, TokenType> twoCharactersTokens {
            {">=", TokenType::GREATER_OR_EQUAL}, {"<=", TokenType::LESS_OR_EQUAL},
            {"==", TokenType::EQUAL}, {"!=", TokenType::NOT_EQUAL},
            {"//", TokenType::INT_DIVISION}, {"||", TokenType::OR},
            {"&&", TokenType::AND}
    };
}

MyLangLexer::MyLangLexer(std::istream &i, HandlerType error) : is(i), errorHandler(std::move(error)) {
    i.get(currentChar);
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
    if (is.eof()) {
        currentChar = EOT;
        return false;
    }
    return true;
}

std::optional<Token> MyLangLexer::nextToken() {
    while (isspace(currentChar) && nextCharacter());
    std::optional<Token> result = tryBuildEOT();
    result = result ?: tryBuildSimpleTokens();
    result = result ?: tryBuildNumber() ?: tryBuildIdentifierOrKeyword();
    result = result ?: tryBuildIdentifierOrKeyword() ?: tryBuildComment();
    result = result ?: tryBuildString();
    if (result) {
        return *result;
    }
    errorHandler(position, ErrorType::UnknownToken);
    nextCharacter();
    return {};
}

std::optional<Token> MyLangLexer::tryBuildEOT() {
    if (is.eof())
        return Token(TokenType::END_OF_TEXT, position);
    return {};
}

std::optional<Token> MyLangLexer::tryBuildSimpleTokens() {
    auto it = simpleTokens.find(currentChar);
    if (it == simpleTokens.end())
        return {};
    Position tokenPosition = position;
    if (currentChar == '=' || currentChar == '>' || currentChar == '<' || currentChar == '/' || currentChar == '!'
        || currentChar == '|' || currentChar == '&') {
        const char first = currentChar;
        nextCharacter();
        std::string str = std::string() + first + currentChar;
        auto twoCharactersTokensIt = twoCharactersTokens.find(str);
        if (twoCharactersTokensIt != twoCharactersTokens.end()) {
            nextCharacter();
            return Token(twoCharactersTokensIt->second, tokenPosition);
        }
        if (first != '|' && first != '&')
            return Token(it->second, tokenPosition);
        return {};
    }
    nextCharacter();
    return Token(it->second, tokenPosition);
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
            if ((std::numeric_limits<int>::max() - decimal) / 10 - value > 0)
                value = value * 10 + decimal;
            else
                errorHandler(tokenPosition, ErrorType::IntRangeError);
            nextCharacter();
        }
    }
    if (currentChar != '.')
        return Token(TokenType::INTEGER_VALUE, value, tokenPosition);
    if (!nextCharacter())
        errorHandler(tokenPosition, ErrorType::IncorrectFloatValue);
    int numOfDecimals = 0;
    int fraction = 0;
    while (isdigit(currentChar)) {
        ++numOfDecimals;
        int decimal = currentChar - '0';
        if ((std::numeric_limits<int>::max() - decimal) / 10 > fraction)
            fraction = fraction * 10 + decimal;
        else
            errorHandler(tokenPosition, ErrorType::IntRangeError);
        nextCharacter();
    }
    double floatValue = value + fraction / pow(10, numOfDecimals);
    return Token(TokenType::FLOAT_VALUE, floatValue, tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildIdentifierOrKeyword() {
    if (!isalpha(currentChar) && currentChar != '_')
        return {};
    Position tokenPosition = position;
    std::string str;
    int size = 0;

    while (isalpha(currentChar) || isdigit(currentChar) || currentChar == '_') {
        str += currentChar;
        nextCharacter();
        if (++size >= MAX_IDENTIFIER_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongIdentifier);
            break;
        }
    }
    auto it = keywords.find(str);
    if (it != keywords.end())
        return Token(it->second, tokenPosition);
    return Token(TokenType::IDENTIFIER, str, tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildComment() {
    if (currentChar != '$')
        return {};
    Position tokenPosition = position;
    std::string str;
    int size = 0;
    nextCharacter();
    while (currentChar != '\n' && currentChar != '\r' && currentChar != EOT) {
        str += currentChar;
        if (++size >= MAX_COMMENT_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongComment);
            break;
        }
        nextCharacter();
    }
    return Token(TokenType::COMMENT, str, tokenPosition);
}

std::optional<Token> MyLangLexer::tryBuildString() {
    if (currentChar != '"')
        return {};
    Position tokenPosition = position;
    nextCharacter();
    std::string str;
    int size = 0;
    while (currentChar != '"' && currentChar != EOT) {
        if (currentChar == '\\') {
            nextCharacter();
            auto it = specialChars.find(currentChar);
            if (it == specialChars.end())
                errorHandler(position, ErrorType::UnknownEscapeCharacter);
            else if (currentChar != EOT)
                str += it->second;
        } else {
            str += currentChar;
        }
        nextCharacter();
        if (++size >= MAX_STRING_LITERAL_LENGTH) {
            errorHandler(tokenPosition, ErrorType::TooLongStringLiteral);
            break;
        }
    }
    if (currentChar == '"')
        nextCharacter();
    else
        errorHandler(tokenPosition, ErrorType::UnexpectedEndOfText);
    return Token(TokenType::STRING_LITERAL, str, tokenPosition);
}
