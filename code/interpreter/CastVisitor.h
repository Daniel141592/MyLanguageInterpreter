#ifndef CODE_CASTVISITOR_H
#define CODE_CASTVISITOR_H

#include <sstream>
#include "../structure/ConstantType.h"
#include "Value.h"

class CastVisitor {
    ConstantType to;
    Value& result;
public:
    CastVisitor(ConstantType t, Value& r);
    void operator()(double from);
    void operator()(int from);
    void operator()(const std::string& from);
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
};


#endif //CODE_CASTVISITOR_H
