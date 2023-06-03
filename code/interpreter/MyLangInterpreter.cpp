#include "MyLangInterpreter.h"

MyLangInterpreter::MyLangInterpreter(std::ostream &o, std::istream &i, Interpreter::HandlerType onError)
                                    : os(o), is(i), errorHandler(std::move(onError)) {

}

void MyLangInterpreter::criticalError(ErrorType type, const std::string& message) {
    errorHandler(result.getPosition(), type, message);
    throw std::exception();
}

void MyLangInterpreter::execute(const Program &program) {
    try {
        visit(program);
    } catch (const DivisionByZeroException& e) {
        criticalError(ErrorType::DIVISION_BY_ZERO, e.what());
    } catch (const EmptyValueException& e) {
        criticalError(ErrorType::EMPTY_VALUE, e.what());
    } catch (const UnknownIdentifierException& e) {
        criticalError(ErrorType::UNKNOWN_IDENTIFIER, e.what()+e.getIdentifier());
    } catch (const RedefinitionException& e) {
        criticalError(ErrorType::IDENTIFIER_REDEFINITION, e.what()+e.getIdentifier());
    } catch (const IncorrectArgsCountException& e) {
        std::ostringstream oss;
        oss << e.what() << "expected: " << e.getExpected() << ", provided: " << e.getProvided();
        criticalError(ErrorType::INCORRECT_ARGS_COUNT, oss.str());
    } catch (const InvalidOperandsException& e) {
        criticalError(ErrorType::INVALID_OPERAND,
                      std::string(e.what()) + "first: " + e.getFirst() + ", second: " + e.getSecond());
    } catch (const IncompatibleTypeException& e) {
        criticalError(ErrorType::INCOMPATIBLE_DATA_TYPES,
                      std::string(e.what()) + "expected: " + e.getExpected() + ", provided: " + e.getProvided());
    } catch (const InvalidConversionException& e) {
        criticalError(ErrorType::INVALID_CONVERSION, std::string(e.what())+"from: "+e.getFrom()+", to: "+e.getTo());
    } catch (const OutOfRangeException& e) {
        criticalError(ErrorType::OUT_OF_RANGE, e.what());
    } catch (const InvalidUnaryOperandException& e) {
        criticalError(ErrorType::INVALID_OPERAND, std::string(e.what())+e.getType());
    } catch (const ReassignImmutableVariableException& e) {
        criticalError(ErrorType::REASSIGN_IMMUTABLE_VARIABLE, std::string(e.what())+e.getIdentifier());
    }
}

void MyLangInterpreter::visit(const Program &program) {
    contexts.emplace_back();
    contexts.back().addScope();
    std::vector<Instruction::InstructionPtr> instructions;
    instructions.emplace_back(std::make_unique<StandardOutput>(os));
    FunctionDeclaration standardOutput(Position(-1, -1), "standardOutput",
                                       std::make_unique<Block>(std::move(instructions)));
    contexts.back().addFunction(standardOutput);
    for (auto &ins: program.getInstructions()) {
        ins->accept(*this);
    }
}

void MyLangInterpreter::visit(const Block &block) {
    for (auto &ins: block.getInstructions()) {
        ins->accept(*this);
        if (result.isReturned()) {
            return;
        }
    }
}

void MyLangInterpreter::visit(const OrExpression &orExpression) {
    result.setPosition(orExpression.getPosition());
    orExpression.getLeft()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue());
    if (std::holds_alternative<int>(result.getValue()) && std::get<int>(result.getValue()) != 0)
        return;
    orExpression.getRight()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue());
}

void MyLangInterpreter::visit(const AndExpression &andExpression) {
    result.setPosition(andExpression.getPosition());
    andExpression.getLeft()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue());
    if (!std::holds_alternative<int>(result.getValue()) || std::get<int>(result.getValue()) == 0)
        return;
    andExpression.getRight()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue());
}

class VariableDeclarationVisitor {
    Context& context;
    const std::string& name;
public:
    VariableDeclarationVisitor(Context& c, const std::string& n) : context(c), name(n) {}

    template<typename T>
    void operator()(const T& value) {
        context.addVariable(name, Variable(value, true));
    }

    void operator()(VariableType) {
        throw EmptyValueException();
    }
};

void MyLangInterpreter::visit(const VariableDeclaration &variableDeclaration) {
    result.setPosition(variableDeclaration.getIdentifier()->getPosition());
    const std::string& name = variableDeclaration.getIdentifier()->getName();
    if (contexts.back().variableDeclaredInCurrentScope(name))
        criticalError(ErrorType::VARIABLE_REDEFINITION, name);
    if (variableDeclaration.getExpression() == nullptr) {
        contexts.back().addVariable(name, Variable());
        return;
    }
    result.setPosition(variableDeclaration.getExpression()->getPosition());
    variableDeclaration.getExpression()->accept(*this);
    std::visit(VariableDeclarationVisitor(contexts.back(), name), result.getValue());
}

void MyLangInterpreter::visit(const FunctionDeclaration &functionDeclaration) {
    result.setPosition(functionDeclaration.getIdentifier().getPosition());
    contexts.back().addFunction(functionDeclaration);
}

void MyLangInterpreter::visit(const Identifier &identifier) {
    result.setPosition(identifier.getPosition());
    auto opt = contexts.back().findVariable(identifier.getName());
    if (!opt) {
        result = Value(identifier.getPosition());
        throw UnknownIdentifierException(identifier.getName());
    }
    std::visit([&](const auto& v) {
        result = Value(identifier.getPosition(), v);
    }, opt.value().getValue());
}

void MyLangInterpreter::visit(const Argument &argument) {
    result = Value(argument.getIdentifier().getPosition(), argument.getIdentifier().getName());
}

class AssignVisitor {
    Context& context;
    const std::string& name;
public:
    AssignVisitor(Context& c, const std::string& n) : context(c), name(n) {}

    template<typename T>
    void operator()(const T& value) {
        context.updateVariable(name, value);
    }

    void operator()(VariableType) {
        throw EmptyValueException();
    }
};

void MyLangInterpreter::visit(const Assign &assign) {
    result.setPosition(assign.getExpression()->getPosition());
    assign.getExpression()->accept(*this);
    result.setPosition(assign.getIdentifier()->getPosition());
    std::visit(AssignVisitor(contexts.back(), assign.getIdentifier()->getName()), result.getValue());
}

void MyLangInterpreter::visit(const IfStatement &ifStatement) {
    result.setPosition(ifStatement.getCondition()->getPosition());
    ifStatement.getCondition()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue());
    if (std::holds_alternative<int>(result.getValue()) && std::get<int>(result.getValue()) != 0) {
        contexts.back().addScope();
        ifStatement.getBlock()->accept(*this);
        contexts.back().removeScope();
    } else if (ifStatement.getElseBlock() != nullptr) {
        contexts.back().addScope();
        ifStatement.getElseBlock()->accept(*this);
        contexts.back().removeScope();
    }
}

void MyLangInterpreter::visit(const LoopStatement &loopStatement) {
    result.setPosition(loopStatement.getCondition()->getPosition());
    loopStatement.getCondition()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue());
    while (std::holds_alternative<int>(result.getValue()) && std::get<int>(result.getValue()) != 0) {
        contexts.back().addScope();
        loopStatement.getBlock()->accept(*this);
        contexts.back().removeScope();
        loopStatement.getCondition()->accept(*this);
        std::visit(BooleanVisitor(result), result.getValue());
    }
}

void MyLangInterpreter::visit(const PatternStatement &patternStatement) {
    result.setPosition(patternStatement.getExpression()->getPosition());
    patternStatement.getExpression()->accept(*this);
    contexts.back().setMatching(result);
    for (const auto& match : patternStatement.getMatches()) {
        match->accept(*this);
        if (!contexts.back().getMatching())
            break;
    }
    contexts.back().endMatching();
}

void MyLangInterpreter::visit(const ReturnStatement &returnStatement) {
    if (returnStatement.getExpression() != nullptr)
        returnStatement.getExpression()->accept(*this);
    else
        result.setValue({});
    result.setReturned();
}

void MyLangInterpreter::visit(const FunctionCall &functionCall) {
    result.setPosition(functionCall.getPosition());
    const auto& functionDeclaration = contexts.back().findFunction(functionCall.getName().getName());
    const auto& args = functionCall.getArgs();
    const auto& argsNames = functionDeclaration.getArguments();
    // TODO zastanowić się nad tym jeszcze
    if (argsNames) {
        if (args.size() != argsNames->size())
            throw IncorrectArgsCountException(argsNames->size(), args.size());
        ScopePtr scope = std::make_shared<Scope>();
        for (int i = 0; i < args.size(); i++) {
            args[i]->accept(*this);
            Value argValue = result;
            Variable var;
            std::visit(PassFunctionArgumentVisitor(var), argValue.getValue());
            scope->addVariable(argsNames.value()[i].getIdentifier().getName(), var);
        }
        contexts.emplace_back(functionCall.getName().getName(), contexts.back().getGlobalScope(), scope);
        functionDeclaration.getFunctionBody()->accept(*this);
        if (result.isReturned())
            result.setReturned(false);
        else
            result.setValue({});
        contexts.pop_back();
    } else {
        contexts.back().setFunctionArgs(&args);
        functionDeclaration.getFunctionBody()->accept(*this);
    }
}

void MyLangInterpreter::visit(const RelativeExpression &relativeExpression) {
    result.setPosition(relativeExpression.getPosition());
    relativeExpression.getLeft()->accept(*this);
    Value first = result;
    try {
        relativeExpression.getRight()->accept(*this);
    } catch (const UnknownIdentifierException& e) {
        if (!result.getOptionalValue() || !std::holds_alternative<SimplePair>(result.getValue())) {
            throw;
        }
    }
    std::visit(RelativeVisitor(result, relativeExpression.getRelativeType()), first.getValue(), result.getValue());
    std::visit(BooleanVisitor(result), result.getValue());
}

void MyLangInterpreter::visit(const AdditiveExpression &additiveExpression) {
    result.setPosition(additiveExpression.getPosition());
    additiveExpression.getLeft()->accept(*this);
    const Value first = result;
    additiveExpression.getRight()->accept(*this);
    std::visit(AdditiveVisitor(result, additiveExpression.getAdditiveType()), first.getValue(), result.getValue());
}

void MyLangInterpreter::visit(const MultiplicationExpression &multiplicationExpression) {
    result.setPosition(multiplicationExpression.getPosition());
    multiplicationExpression.getLeft()->accept(*this);
    const Value first = result;
    multiplicationExpression.getRight()->accept(*this);
    std::visit(MultiplicativeVisitor(result, multiplicationExpression.getMultiplicativeType()), first.getValue(),
               result.getValue());
}

void MyLangInterpreter::visit(const Constant &constant) {
    result.setPosition(constant.getPosition());
    if (constant.getConstantType() == ConstantType::STRING)
        result = Value(constant.getPosition(), std::get<std::string>(constant.getValue()));
    else if (constant.getConstantType() == ConstantType::INTEGER)
        result = Value(constant.getPosition(), std::get<int>(constant.getValue()));
    else if (constant.getConstantType() == ConstantType::FLOAT)
        result = Value(constant.getPosition(), std::get<double>(constant.getValue()));
}

class FieldVisitor {
    Value& result;
    FieldType type;
public:
    FieldVisitor(Value& v, FieldType t) : result(v), type(t) {}

    void operator()(const SimplePair& pair) {
        std::visit([&](const auto& v) {
            result.setValue(v);
        }, type == FieldType::FIRST ? pair.first.value() : pair.second.value());
    }

    template<typename T>
    void operator()(const T& v) {
        throw InvalidUnaryOperandException(v);
    }
};

void MyLangInterpreter::visit(const Field &field) {
    result.setPosition(field.getPosition());
    field.getExpression()->accept(*this);
    std::visit(FieldVisitor(result, field.getFieldType()), result.getValue());
}

void MyLangInterpreter::visit(const CastExpression &castExpression) {
    result.setPosition(castExpression.getPosition());
    castExpression.getExpression()->accept(*this);
    std::visit(CastVisitor(castExpression.getType(), result), result.getValue());
}

class NegationVisitor {
    Value& result;
public:
    explicit NegationVisitor(Value& r) : result(r) {}

    void operator()(const std::string& str) {
        throw InvalidUnaryOperandException(str);
    }

    void operator()(const SimplePair&) {
        throw InvalidUnaryOperandException(VariableType::PAIR);
    }

    void operator()(VariableType) {
        throw EmptyValueException();
    }

    template<typename T>
    void operator()(const T& value) {
        result.setValue(-value);
    }
};

void MyLangInterpreter::visit(const NegatedExpression &negatedExpression) {
    result.setPosition(negatedExpression.getPosition());
    negatedExpression.getExpression()->accept(*this);
    if (negatedExpression.getNegationType() == NegationType::LOGICAL) {
        std::visit(BooleanVisitor(result), result.getValue());
        int value = std::get<int>(result.getValue());
        result.setValue(value == 0 ? 1 : 0);
        return;
    }
    std::visit(NegationVisitor(result), result.getValue());
}

class MatchExpressionVisitor {
    std::optional<std::variant<Constant, Pair>>& constantOrPair;
    Position position;
public:
    MatchExpressionVisitor(Position p, std::optional<std::variant<Constant, Pair>>& c) : position(p), constantOrPair(c) {}

    void operator()(const SimplePair& simplePair) {
        std::optional<std::variant<Constant, Pair>> firstConstant;
        std::visit(MatchExpressionVisitor(position, firstConstant), simplePair.first.value());
        std::optional<std::variant<Constant, Pair>> secondConstant;
        std::visit(MatchExpressionVisitor(position, secondConstant), simplePair.second.value());
        constantOrPair = Pair(std::make_unique<Constant>(std::get<Constant>(firstConstant.value())),
                  std::make_unique<Constant>(std::get<Constant>(secondConstant.value())));
    }

    void operator()(VariableType) {
        throw EmptyValueException();
    }

    template<typename T>
    void operator()(const T& value) {
        constantOrPair = Constant(position, value);
    }
};

void MyLangInterpreter::visit(const MatchExpression &matchExpression) {
    result.setPosition(matchExpression.getIdentifier()->getPosition());
    const Value& matchingValue = contexts.back().getMatching().value();
    try {
        matchExpression.getExpression()->accept(*this);
        std::visit(RelativeVisitor(result, RelativeType::IS), matchingValue.getValue(), result.getValue());
    } catch (const UnknownIdentifierException& e) {
        std::vector<Expression::ExpressionPtr> args;
        std::optional<std::variant<Constant, Pair>> constantOrPair;
        std::visit(MatchExpressionVisitor(matchExpression.getExpression()->getPosition(), constantOrPair),
                   matchingValue.getValue());
        if (std::holds_alternative<Constant>(constantOrPair.value())) {
            args.push_back(std::make_unique<Constant>(std::get<Constant>(constantOrPair.value())));
        } else if (std::holds_alternative<Pair>(constantOrPair.value())) {
            args.push_back(std::make_unique<Pair>(std::move(std::get<Pair>(constantOrPair.value()))));
        }
        Identifier id(matchExpression.getExpression()->getPosition(), e.getIdentifier());
        FunctionCall functionCall(id, std::move(args));
        visit(functionCall);
        std::visit(BooleanVisitor(result), result.getValue());
    }
    if (!std::holds_alternative<int>(result.getValue()) || std::get<int>(result.getValue()) == 0)
        return;
    contexts.back().addScope();
    std::visit(AssignVisitor(contexts.back(), matchExpression.getIdentifier()->getName()), matchingValue.getValue());
    matchExpression.getBlock()->accept(*this);
    contexts.back().removeScope();
    contexts.back().endMatching();
}

void MyLangInterpreter::visit(const MatchPair &matchPair) {
    result.setPosition(matchPair.getFirst()->getPosition());
    const Value& matchingValue = contexts.back().getMatching().value();
    if (!std::holds_alternative<SimplePair>(matchingValue.getValue()))
        return;
    SimplePair matchingPair = std::get<SimplePair>(matchingValue.getValue());
    std::optional<SimpleType> firstFieldOptional, secondFieldOptional;
    contexts.back().addScope();
    try {
        matchPair.getFirst()->accept(*this);
        std::visit((IncompletePairVisitor(firstFieldOptional)), result.getValue());
    } catch (const UnknownIdentifierException& e) {
        std::visit(AssignVisitor(contexts.back(), e.getIdentifier()), matchingPair.first.value());
    }
    try {
        matchPair.getSecond()->accept(*this);
        std::visit((IncompletePairVisitor(secondFieldOptional)), result.getValue());
    } catch (const UnknownIdentifierException& e) {
        std::visit(AssignVisitor(contexts.back(), e.getIdentifier()), matchingPair.second.value());
    }
    SimplePair matchedPair(firstFieldOptional, secondFieldOptional);
    std::visit(RelativeVisitor(result, RelativeType::IS), matchingValue.getValue(), ValueType(matchedPair));
    if (!std::holds_alternative<int>(result.getValue()) || std::get<int>(result.getValue()) == 0) {
        contexts.back().removeScope();
        return;
    }
    matchPair.getBlock()->accept(*this);
    contexts.back().removeScope();
    contexts.back().endMatching();
}

void MyLangInterpreter::visit(const MatchType &matchType) {
    result.setPosition(matchType.getIdentifier()->getPosition());
    ValueType valueType;
    switch (matchType.getConstantType().value()) {
        case ConstantType::INTEGER:
            valueType = VariableType::INTEGER;
            break;
        case ConstantType::FLOAT:
            valueType = VariableType::FLOAT;
            break;
        case ConstantType::STRING:
            valueType = VariableType::STRING;
            break;
    }
    const Value& value = contexts.back().getMatching().value();
    std::visit(RelativeVisitor(result, RelativeType::IS), value.getValue(), valueType);
    if (std::get<int>(result.getValue()) == 0)
        return;
    contexts.back().addScope();
    std::visit(AssignVisitor(contexts.back(), matchType.getIdentifier()->getName()), value.getValue());
    matchType.getBlock()->accept(*this);
    contexts.back().removeScope();
    contexts.back().endMatching();
}

void MyLangInterpreter::visit(const MatchNone &matchNone) {
    contexts.back().endMatching();
    contexts.back().addScope();
    matchNone.getBlock()->accept(*this);
    contexts.back().removeScope();
}

void MyLangInterpreter::visit(const Pair &pair) {
    result.setPosition(pair.getPosition());
    std::optional<SimpleType> firstFieldOptional, secondFieldOptional;
    std::string unknownIdentifier;
    try {
        pair.getFirst()->accept(*this);
        std::visit((IncompletePairVisitor(firstFieldOptional)), result.getValue());
    } catch (const UnknownIdentifierException& e) {
        unknownIdentifier = e.getIdentifier();
    }
    try {
        pair.getSecond()->accept(*this);
        std::visit((IncompletePairVisitor(secondFieldOptional)), result.getValue());
    } catch (const UnknownIdentifierException& e) {
        unknownIdentifier = unknownIdentifier.empty() ? e.getIdentifier() : unknownIdentifier;
    }
    if (firstFieldOptional && secondFieldOptional) {
        std::visit(PairVisitor(result), firstFieldOptional.value(), secondFieldOptional.value());
        return;
    }
    result.setValue(SimplePair(firstFieldOptional, secondFieldOptional), result.getPosition());
    throw UnknownIdentifierException(unknownIdentifier);
}

void MyLangInterpreter::visit(const Typename &type) {
    result.setPosition(type.getPosition());
    switch (type.getType()) {
        case ConstantType::INTEGER:
            result.setValue(VariableType::INTEGER);
            break;
        case ConstantType::FLOAT:
            result.setValue(VariableType::FLOAT);
            break;
        case ConstantType::STRING:
            result.setValue(VariableType::STRING);
            break;
    }
}

void MyLangInterpreter::visit(const StandardOutput &standardOutput) {
    for (const auto& arg : *contexts.back().getFunctionArgs()) {
        arg->accept(*this);
        standardOutput.print(result);
    }
    os << '\n';
}
