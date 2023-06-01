#include "MyLangInterpreter.h"
#include "MultiplicativeVisitor.h"
#include "AdditiveVisitor.h"
#include "BooleanVisitor.h"

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
    } catch (const IncorrectArgsCount& e) {
        std::ostringstream oss;
        oss << e.what() << "expected: " << e.getExpected() << ", provided: " << e.getProvided();
        criticalError(ErrorType::INCORRECT_ARGS_COUNT, oss.str());
    } catch (const InvalidOperands& e) {
        criticalError(ErrorType::INVALID_OPERAND,
                      std::string(e.what()) + "first: " + e.getFirst() + ", second: " + e.getSecond());
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

void MyLangInterpreter::visit(const VariableDeclaration &variableDeclaration) {
    result.setPosition(variableDeclaration.getExpression()->getPosition());
    const std::string& name = variableDeclaration.getIdentifier()->getName();
    if (contexts.back().variableDeclaredInCurrentScope(name))
        criticalError(ErrorType::VARIABLE_REDEFINITION, name);
    if (variableDeclaration.getExpression() == nullptr) {
        contexts.back().addVariable(name, Variable(0, true));   //TODO przydało by się zrobić pustą wartość, a nie 0
        return;
    }
    variableDeclaration.getExpression()->accept(*this);
    std::visit([&](const auto& value) {
        contexts.back().addVariable(name, Variable(value, true));
    }, result.getValue());
}

void MyLangInterpreter::visit(const FunctionDeclaration &functionDeclaration) {
    result.setPosition(functionDeclaration.getIdentifier().getPosition());
    contexts.back().addFunction(functionDeclaration);
}

void MyLangInterpreter::visit(const Identifier &identifier) {
    result.setPosition(identifier.getPosition());
    auto opt = contexts.back().findVariable(identifier.getName());
    if (!opt)
        criticalError(ErrorType::UNDEFINED_VARIABLE, identifier.getName());
    std::visit([&](const auto& v) {
        result = Value(identifier.getPosition(), v);
    }, opt.value().getValue());
}

void MyLangInterpreter::visit(const Argument &argument) {
    result = Value(argument.getIdentifier().getPosition(), argument.getIdentifier().getName());
}

struct AssignVisitor {
    const std::string& name;
    Context& context;
    AssignVisitor(const std::string& n, Context& c) : name(n), context(c) {};
    template<typename T>
    void operator()(T value) {
        context.updateVariable(name, value);
    }
    void operator()(std::string value) {
        context.updateVariable(name, std::move(value));
    }
};

void MyLangInterpreter::visit(const Assign &assign) {
    result.setPosition(assign.getExpression()->getPosition());
    assign.getExpression()->accept(*this);
    result.setPosition(assign.getIdentifier()->getPosition());
    std::visit(AssignVisitor(assign.getIdentifier()->getName(), contexts.back()), result.getValue());
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
    // TODO już się nie mogę doczekać...
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
            throw IncorrectArgsCount(argsNames->size(), args.size());
        ScopePtr scope = std::make_shared<Scope>();
        for (int i = 0; i < args.size(); i++) {
            args[i]->accept(*this);
            Value argValue = result;
            std::visit([&](const auto& value) {
                scope->addVariable(argsNames.value()[i].getIdentifier().getName(), Variable(value, false));
            }, argValue.getValue());
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
    relativeExpression.getRight()->accept(*this);
    if (first.getType() != ConstantType::INTEGER && first.getType() != ConstantType::FLOAT)
        throw InvalidOperands(first.getType(), result.getType());
    switch (relativeExpression.getRelativeType()) {
        case RelativeType::EQUAL:
            result.setValue(first.getValue() == result.getValue());
            break;
        case RelativeType::NOT_EQUAL:
            result.setValue(first.getValue() != result.getValue());
            break;
        case RelativeType::GREATER:
            result.setValue(first.getValue() > result.getValue());
            break;
        case RelativeType::LESS:
            result.setValue(first.getValue() < result.getValue());
            break;
        case RelativeType::GREATER_EQUAL:
            result.setValue(first.getValue() >= result.getValue());
            break;
        case RelativeType::LESS_EQUAL:
            result.setValue(first.getValue() <= result.getValue());
            break;
        case RelativeType::IS:
            //TODO no i tutaj zaczynają się schody...
            break;
    }
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

void MyLangInterpreter::visit(const Field &field) {

}

void MyLangInterpreter::visit(const CastExpression &castExpression) {

}

void MyLangInterpreter::visit(const NegatedExpression &negatedExpression) {

}

void MyLangInterpreter::visit(const MatchExpression &matchExpression) {

}

void MyLangInterpreter::visit(const MatchPair &matchPair) {

}

void MyLangInterpreter::visit(const MatchType &matchType) {

}

void MyLangInterpreter::visit(const MatchNone &matchNone) {

}

void MyLangInterpreter::visit(const Pair &pair) {

}

void MyLangInterpreter::visit(const Typename &type) {

}

void MyLangInterpreter::visit(const StandardOutput &standardOutput) {
    for (const auto& arg : *contexts.back().getFunctionArgs()) {
        arg->accept(*this);
        standardOutput.print(result);
    }
    os << '\n';
}
