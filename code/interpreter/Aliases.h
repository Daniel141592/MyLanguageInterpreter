#ifndef CODE_ALIASES_H
#define CODE_ALIASES_H

#include "VariableType.h"

using SimpleType = std::variant<int, double, std::string>;
using SimplePair = std::pair<std::optional<SimpleType>, std::optional<SimpleType>>;
using ValueType = std::variant<int, double, std::string, SimplePair, VariableType>;

#endif //CODE_ALIASES_H
