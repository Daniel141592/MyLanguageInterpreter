#ifndef CODE_ALIASES_H
#define CODE_ALIASES_H

using SimpleType = std::variant<int, double, std::string>;
using SimplePair = std::pair<SimpleType, SimpleType>;
using ValueType = std::variant<int, double, std::string, SimplePair>;

#endif //CODE_ALIASES_H
