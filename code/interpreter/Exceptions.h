#ifndef CODE_EXCEPTIONS_H
#define CODE_EXCEPTIONS_H

#include <exception>
#include <string>
#include <utility>
#include <unordered_map>
#include "VariableType.h"
#include "Aliases.h"

namespace {
    std::unordered_map<VariableType, std::string> typesToString = {
            {VariableType::INTEGER, "integer"},
            {VariableType::FLOAT, "float"},
            {VariableType::STRING, "string"},
            {VariableType::PAIR, "pair"}
    };

    VariableType variableType(int) {
        return VariableType::INTEGER;
    }

    VariableType variableType(double) {
        return VariableType::FLOAT;
    }

    VariableType variableType(const std::string &) {
        return VariableType::STRING;
    }

    VariableType variableType(const SimplePair&) {
        return VariableType::PAIR;
    }
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
    explicit UnknownIdentifierException(std::string identifier)
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
    VariableType expected_;
    VariableType provided_;
public:
    IncompatibleTypeException() = default;
    IncompatibleTypeException(VariableType expected, VariableType provided)
                : expected_(expected), provided_(provided) {}
    template<typename T, typename U>
    IncompatibleTypeException(const T& first, const U& second)
            : expected_(variableType(first)), provided_(variableType(second)) {}
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
    explicit ReassignImmutableVariableException(std::string identifier)
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
    VariableType first_;
    VariableType second_;

public:
    InvalidOperandsException() = default;
    InvalidOperandsException(VariableType first, VariableType second)
            : first_(first), second_(second) {}
    template<typename T, typename U>
    InvalidOperandsException(const T& first, const U& second)
            : first_(variableType(first)), second_(variableType(second)) {}

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

class InvalidUnaryOperandException : public std::exception {
    VariableType type_;
public:
    InvalidUnaryOperandException() = default;
    explicit InvalidUnaryOperandException(VariableType type) : type_(type) {}
    template<typename T>
    explicit InvalidUnaryOperandException(T type) : type_(variableType(type)) {}

    const char * what() const noexcept override {
        return "Invalid unary operand: ";
    }

    const std::string& getType() const {
        return typesToString[type_];
    }
};

class InvalidConversionException : public std::exception {
    VariableType from_;
    VariableType to_;
public:
    InvalidConversionException() = default;
    InvalidConversionException(VariableType first, VariableType second)
            : from_(first), to_(second) {}
    template<typename T, typename U>
    InvalidConversionException(T first, U second)
            : from_(variableType(first)), to_(variableType(second)) {}

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
