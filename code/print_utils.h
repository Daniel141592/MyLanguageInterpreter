#ifndef CODE_PRINT_UTILS_H
#define CODE_PRINT_UTILS_H

#include <string_view>
#include <unordered_map>

#include "lexer/ErrorType.h"
#include "TokenType.h"

namespace PrintUtils {
    std::string_view toString(ErrorType errorType);
    std::string_view toString(TokenType tokenType);
}

#endif //CODE_PRINT_UTILS_H
