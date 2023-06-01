#ifndef CODE_EXCEPTIONS_H
#define CODE_EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>
#include <unordered_map>

namespace {
    std::unordered_map<ConstantType, std::string> typesToString = {
            {ConstantType::INTEGER, "integer"},
            {ConstantType::FLOAT, "float"},
            {ConstantType::STRING, "string"}
    };
}


class DivisionByZeroException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Division by zero";
    }
};

class EmptyValueException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Empty value";
    }
};

class UnknownIdentifierException : public std::exception {
    std::string identifier_;

public:
    UnknownIdentifierException(std::string identifier)
            : identifier_(std::move(identifier)) {}

    const char* what() const noexcept override {
        return "Unknown identifier: ";
    }

    const std::string& getIdentifier() const {
        return identifier_;
    }
};

class RedefinitionException : public std::exception {
    std::string identifier_;
public:
    explicit RedefinitionException(std::string identifier)
            : identifier_(std::move(identifier)) {}

    const char* what() const noexcept override {
        return "Redefinition of identifier: ";
    }

    const std::string& getIdentifier() const {
        return identifier_;
    }
};

class IncompatibleTypeException : public std::exception {
    ConstantType expected_;
    ConstantType provided_;
public:
    IncompatibleTypeException() = default;
    IncompatibleTypeException(ConstantType expected, ConstantType provided)
                : expected_(expected), provided_(provided) {}
    const char * what() const noexcept override {
        return "Incompatible type: ";
    }

    const std::string& getExpected() const {
        return typesToString[expected_];
    }

    const std::string& getProvided() const {
        return typesToString[provided_];
    }
};

class ReassignImmutableVariableException : public std::exception {
    std::string identifier_;
public:
    ReassignImmutableVariableException() = default;
    ReassignImmutableVariableException(std::string identifier)
            : identifier_(std::move(identifier)) {}
    const char * what() const noexcept override {
        return "Reassign immutable variable: ";
    }

    const std::string& getIdentifier() const {
        return identifier_;
    }
};

class IncorrectArgsCountException : public std::exception {
    int expected_;
    int provided_;
public:
    IncorrectArgsCountException() = default;
    IncorrectArgsCountException(int expected, int provided)
            : expected_(expected), provided_(provided) {}
    const char * what() const noexcept override {
        return "Incorrect args count: ";
    }

    int getExpected() const {
        return expected_;
    }

    int getProvided() const {
        return provided_;
    }
};

class InvalidOperandsException : public std::exception {
    ConstantType first_;
    ConstantType second_;

    ConstantType constantType(int) {
        return ConstantType::INTEGER;
    }

    ConstantType constantType(double) {
        return ConstantType::FLOAT;
    }

    ConstantType constantType(std::string) {
        return ConstantType::STRING;
    }
public:
    InvalidOperandsException() = default;
    InvalidOperandsException(ConstantType first, ConstantType second)
            : first_(first), second_(second) {}
    template<typename T, typename U>
    InvalidOperandsException(T first, U second)
            : first_(constantType(first)), second_(constantType(second)) {}

    const char * what() const noexcept override {
        return "Invalid operands: ";
    }

    const std::string& getFirst() const {
        return typesToString[first_];
    }

    const std::string& getSecond() const {
        return typesToString[second_];
    }
};

class InvalidConversionException : public std::exception {
    ConstantType from_;
    ConstantType to_;

    ConstantType constantType(int) {
        return ConstantType::INTEGER;
    }

    ConstantType constantType(double) {
        return ConstantType::FLOAT;
    }

    ConstantType constantType(std::string) {
        return ConstantType::STRING;
    }
public:
    InvalidConversionException() = default;
    InvalidConversionException(ConstantType first, ConstantType second)
            : from_(first), to_(second) {}
    template<typename T, typename U>
    InvalidConversionException(T first, U second)
            : from_(constantType(first)), to_(constantType(second)) {}

    const char * what() const noexcept override {
        return "Invalid conversion: ";
    }

    const std::string& getFrom() const {
        return typesToString[from_];
    }

    const std::string& getTo() const {
        return typesToString[to_];
    }
};

class OutOfRangeException : public std::exception {
public:
    OutOfRangeException() = default;
    const char * what() const noexcept override {
        return "Out of range: ";
    }
};

#endif //CODE_EXCEPTIONS_H
