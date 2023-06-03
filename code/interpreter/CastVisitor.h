#ifndef CODE_CASTVISITOR_H
#define CODE_CASTVISITOR_H

#include <sstream>
#include "../structure/ConstantType.h"
#include "Value.h"
#include "Aliases.h"

class CastVisitor {
    VariableType to;
    Value& result;
public:
    CastVisitor(VariableType t, Value& r);
    CastVisitor(ConstantType t, Value& r);
    void operator()(double from);
    void operator()(int from);
    void operator()(const std::string& from);
    void operator()(const SimplePair& from);
    void operator()(VariableType);
private:
    template<typename T>
    void convertFromString(const std::string& from) {
        T converted;
        try {
            converted = std::stod(from);
            result.setValue(converted);
        } catch (const std::invalid_argument&) {
            throw InvalidConversionException(from, converted);
        } catch (const std::out_of_range&) {
            throw OutOfRangeException();
        }
    }
    template<typename T>
    void convertToString(T from) {
        std::stringstream ss;
        ss << from;
        result.setValue(ss.str());
    }

    void convertToString(const SimplePair& from) {
        std::stringstream ss;
        std::visit([&](const auto& f, const auto& s) {
            ss << f << ", " << s;
        }, from.first.value(), from.second.value());
    }
};


#endif //CODE_CASTVISITOR_H
