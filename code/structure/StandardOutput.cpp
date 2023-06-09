#include "StandardOutput.h"

StandardOutput::StandardOutput(std::ostream &o) : os(o) {

}

void StandardOutput::accept(Visitor &visitor) const {
    visitor.visit(*this);
}

class PrintVisitor {
    std::string& result;
public:
    explicit PrintVisitor(std::string& s) : result(s) {}
    void operator()(const SimplePair& value) {
        std::visit([&](const auto& f, const auto& s) {
            std::ostringstream os;
            os << f << ", " << s;
            result = os.str();
        }, value.first.value(), value.second.value());
    }

    void operator()(VariableType) {
        throw EmptyValueException();
    }

    template<typename T>
    void operator()(const T& value) {
        std::ostringstream os;
        os << value;
        result = os.str();
    }
};

void StandardOutput::print(const VariableValueTypename& value) const {
    std::string str;
    std::visit(PrintVisitor(str), value);
    os << str;
}
