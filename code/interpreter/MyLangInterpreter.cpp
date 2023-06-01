#include "MyLangInterpreter.h"
#include "MultiplicativeVisitor.h"
#include "AdditiveVisitor.h"
#include "BooleanVisitor.h"

MyLangInterpreter::MyLangInterpreter(std::ostream &o, std::istream &i, Interpreter::HandlerType onError)
                                                                    : os(o), is(i), errorHandler(std::move(onError)) {

}

void MyLangInterpreter::criticalError(ErrorType type) {
    errorHandler(result.getPosition(), type);
    throw std::exception();
}

void MyLangInterpreter::execute(const Program &program) {
    visit(program);
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
    orExpression.getLeft()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue().value());
    if (std::holds_alternative<int>(result.getValue().value()) && std::get<int>(result.getValue().value()) != 0)
        return;
    orExpression.getRight()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue().value());
}

void MyLangInterpreter::visit(const AndExpression &andExpression) {
    andExpression.getLeft()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue().value());
    if (!std::holds_alternative<int>(result.getValue().value()) || std::get<int>(result.getValue().value()) == 0)
        return;
    andExpression.getRight()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue().value());
}

void MyLangInterpreter::visit(const VariableDeclaration &variableDeclaration) {
    const std::string& name = variableDeclaration.getIdentifier()->getName();
    if (contexts.back().findVariable(name))
        criticalError(ErrorType::VARIABLE_REDEFINITION);
    if (variableDeclaration.getExpression() == nullptr) {
        contexts.back().addVariable(name, Variable(0, true));   //TODO przydało by się zrobić pustą wartość, a nie 0
        return;
    }
    variableDeclaration.getExpression()->accept(*this);
    std::visit([&](const auto& value) {
        contexts.back().addVariable(name, Variable(value, true));
    }, result.getValue().value());
}

void MyLangInterpreter::visit(const FunctionDeclaration &functionDeclaration) {
    contexts.back().addFunction(functionDeclaration);
}

void MyLangInterpreter::visit(const Identifier &identifier) {
    auto opt = contexts.back().findVariable(identifier.getName());
    if (!opt)
        criticalError(ErrorType::UNDEFINED_VARIABLE);
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
    assign.getExpression()->accept(*this);
    std::visit(AssignVisitor(assign.getIdentifier()->getName(), contexts.back()), result.getValue().value());
}

void MyLangInterpreter::visit(const IfStatement &ifStatement) {
    ifStatement.getCondition()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue().value());
    if (std::holds_alternative<int>(result.getValue().value()) && std::get<int>(result.getValue().value()) != 0)
        ifStatement.getBlock()->accept(*this);
    else if (ifStatement.getElseBlock() != nullptr)
        ifStatement.getElseBlock()->accept(*this);
}

void MyLangInterpreter::visit(const LoopStatement &loopStatement) {
    loopStatement.getCondition()->accept(*this);
    std::visit(BooleanVisitor(result), result.getValue().value());
    while (std::holds_alternative<int>(result.getValue().value()) && std::get<int>(result.getValue().value()) != 0) {
        loopStatement.getBlock()->accept(*this);
        loopStatement.getCondition()->accept(*this);
        std::visit(BooleanVisitor(result), result.getValue().value());
    }
}

void MyLangInterpreter::visit(const PatternStatement &patternStatement) {
    // TODO już się nie mogę doczekać...
}

void MyLangInterpreter::visit(const ReturnStatement &returnStatement) {
    returnStatement.getExpression()->accept(*this);
    result.setReturned();
}

void MyLangInterpreter::visit(const FunctionCall &functionCall) {
    try {
        const auto& functionDeclaration = contexts.back().findFunction(functionCall.getName().getName());
        const auto& args = functionCall.getArgs();
        const auto& argsNames = functionDeclaration.getArguments();
        // contexts.back().addScope(); //TODO fix
        contexts.emplace_back(functionCall.getName().getName(), contexts.back().getGlobalScope());
        if (argsNames) {
            if (args.size() != argsNames->size())
                criticalError(ErrorType::INCORRECT_ARGS_COUNT);

            for (int i = 0; i < args.size(); i++) {
                args[i]->accept(*this);
                Value argValue = result;
                std::visit([&](const auto& value) {
                    contexts.back().addVariable(argsNames.value()[i].getIdentifier().getName(), Variable(value, false));
                }, argValue.getValue().value());
            }
        } else {
            contexts.back().setFunctionArgs(&args);
        }
        functionDeclaration.getFunctionBody()->accept(*this);
        if (result.isReturned())
            result.setReturned(false);
        // contexts.back().removeScope();
        contexts.pop_back();
    } catch (...) {
        criticalError(ErrorType::UNDEFINED_FUNCTION);
    }
}

void MyLangInterpreter::visit(const RelativeExpression &relativeExpression) {
    relativeExpression.getLeft()->accept(*this);
    Value first = result;
    relativeExpression.getRight()->accept(*this);
    if (first.getType() != ConstantType::INTEGER && first.getType() != ConstantType::FLOAT)
        criticalError(ErrorType::INVALID_OPERAND);
    switch (relativeExpression.getRelativeType()) {
        case RelativeType::EQUAL:
            result.setValue(first.getValue().value() == result.getValue().value());
            break;
        case RelativeType::NOT_EQUAL:
            result.setValue(first.getValue().value() != result.getValue().value());
            break;
        case RelativeType::GREATER:
            result.setValue(first.getValue().value() > result.getValue().value());
            break;
        case RelativeType::LESS:
            result.setValue(first.getValue().value() < result.getValue().value());
            break;
        case RelativeType::GREATER_EQUAL:
            result.setValue(first.getValue().value() >= result.getValue().value());
            break;
        case RelativeType::LESS_EQUAL:
            result.setValue(first.getValue().value() <= result.getValue().value());
            break;
        case RelativeType::IS:
            //TODO no i tutaj zaczynają się schody...
            break;
    }
}

void MyLangInterpreter::visit(const AdditiveExpression &additiveExpression) {
    additiveExpression.getLeft()->accept(*this);
    const Value first = result;
    additiveExpression.getRight()->accept(*this);
    std::visit(AdditiveVisitor(result, additiveExpression.getAdditiveType(), [&](ErrorType et) {
        criticalError(et);
    }), first.getValue().value(), result.getValue().value());
}

void MyLangInterpreter::visit(const MultiplicationExpression &multiplicationExpression) {
    multiplicationExpression.getLeft()->accept(*this);
    const Value first = result;
    multiplicationExpression.getRight()->accept(*this);
    std::visit(MultiplicativeVisitor(result, multiplicationExpression.getMultiplicativeType(), [&](ErrorType et) {
        criticalError(et);
    }), first.getValue().value(), result.getValue().value());
}

void MyLangInterpreter::visit(const Constant &constant) {
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
