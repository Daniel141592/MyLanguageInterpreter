#include "PrintVisitor.h"

PrintVisitor::PrintVisitor(std::ostream &os) : output(os), indent(0) {

}

PrintVisitor::PrintVisitor() : output(std::cout), indent(0) {}

void PrintVisitor::visit(const Program* program) {
    print("program");
    manageIndent([&]() {
        for (auto &ins: program->getInstructions()) {
            ins->accept(*this);
        }
    });
}

void PrintVisitor::visit(const Block* block) {
    print("block");
    manageIndent([&]() {
        for (auto &ins: block->getInstructions()) {
            ins->accept(*this);
        }
    });
}

void PrintVisitor::visit(const OrExpression* expression) {
    print("or expression");
    manageIndent([&]() {
        if (expression->getLeft()) {
            print("left");
            manageIndent([&]() {
                expression->getLeft()->accept(*this);
            });
        }
        if (expression->getRight()) {
            print("right");
            manageIndent([&]() {
                expression->getRight()->accept(*this);
            });
        }
    });
}

void PrintVisitor::visit(const AndExpression* andExpression) {
    print("and expression");
    manageIndent([&]() {
        if (andExpression->getLeft()) {
            print("left");
            manageIndent([&]() {
                andExpression->getLeft()->accept(*this);
            });
        }
        if (andExpression->getRight()) {
            print("right");
            manageIndent([&]() { andExpression->getRight()->accept(*this); });
        }
    });
}

void PrintVisitor::visit(const VariableDeclaration* variableDeclaration) {
    print("variable declaration");
    manageIndent([&]() {
        if (variableDeclaration->isMut())
            print("mutable: true\n");
        print("name");
        manageIndent([&]() { variableDeclaration->getIdentifier()->accept(*this); });
        if (variableDeclaration->getExpression()) {
            print("expression");
            manageIndent([&]() { variableDeclaration->getExpression()->get()->accept(*this); });
        }
    });
}

void PrintVisitor::visit(const FunctionDeclaration* functionDeclaration) {
    print("function");
    manageIndent([&]() {
        print("name");
        manageIndent([&]() {
            functionDeclaration->getIdentifier().accept(*this);
        });
        if (functionDeclaration->getArguments()) {
            print("arguments");
            manageIndent([&]() {;
            for (auto &arg : *functionDeclaration->getArguments())
                arg.accept(*this);
            });
        }
        functionDeclaration->getFunctionBody()->accept(*this);
    });
}

void PrintVisitor::visit(const Identifier* identifier) {
    print("identifier");
    manageIndent([&]() {
        std::string name = identifier->getName()+'\n';
        print(name.c_str());
    });
}

void PrintVisitor::visit(const Argument* argument) {
    if (argument->isRef())
        print("argument ref");
    else
        print("argument");
    manageIndent([&](){argument->getIdentifier().accept(*this);});
}

void PrintVisitor::visit(const Assign* assign) {
    print("assign");
    manageIndent([&]() {
        print("name");
        manageIndent([&]() {
            assign->getIdentifier()->accept(*this);
        });
        print("expression");
        manageIndent([&]() {
            assign->getExpression()->accept(*this);
        });
    });
}

void PrintVisitor::visit(const IfStatement *ifStatement) {
    print("if");
    manageIndent([&]() {
        print("condition");
        manageIndent([&]() {
            ifStatement->getCondition()->accept(*this);
        });
        ifStatement->getBlock()->accept(*this);
        if (ifStatement->getElseBlock()) {
            print("else");
            manageIndent([&]() {
                ifStatement->getElseBlock().value()->accept(*this);
            });
        }
    });
}

void PrintVisitor::visit(const LoopStatement *loopStatement) {
    print("loop");
    manageIndent([&]() {
        print("condition");
        manageIndent([&](){
            loopStatement->getCondition()->accept(*this);
        });
        loopStatement->getBlock()->accept(*this);
    });
}

void PrintVisitor::visit(const PatternStatement *patternStatement) {
    print("pattern");
    manageIndent([&]() {
        print("expression");
        manageIndent([&]() {
            patternStatement->getExpression()->accept(*this);
        });
        print("matches");
        manageIndent([&](){
            for (auto &m: patternStatement->getMatches()) {
                m->accept(*this);
            }
        });

    });
}

void PrintVisitor::visit(const ReturnStatement *returnStatement) {
    print("return");
    manageIndent([&]() {
        if (returnStatement->getExpression()) {
            print("expression");
            manageIndent([&]() {
                returnStatement->getExpression().value()->accept(*this);
            });
        }
    });
}

void PrintVisitor::visit(const FunctionCall *functionCall) {
    print("function call");
    manageIndent([&]() {
        print("name");
        manageIndent([&]() {
            functionCall->getName().accept(*this);
        });
        print("args");
        manageIndent([&]() {
            for (auto &arg: functionCall->getArgs()) {
                arg->accept(*this);
            }
        });
    });
}

void PrintVisitor::visit(const RelativeExpression *relativeExpression) {
    std::unordered_map<RelativeType, std::string> map = {
            {RelativeType::EQUAL, "EQUAL"},
            {RelativeType::NOT_EQUAL, "NOT_EQUAL"},
            {RelativeType::GREATER, "GREATER"},
            {RelativeType::LESS, "LESS"},
            {RelativeType::GREATER_EQUAL, "GREATER_EQUAL"},
            {RelativeType::LESS_EQUAL, "LESS_EQUAL"},
            {RelativeType::IS, "IS"}
    };
    print(std::string("relative expression, type: "+map[relativeExpression->getRelativeType()]).c_str());
    manageIndent([&]() {
        relativeExpression->getRelativeType();
        if (relativeExpression->getLeft()) {
            print("left");
            manageIndent([&]() {
                relativeExpression->getLeft()->accept(*this);
            });
        }
        if (relativeExpression->getRight()) {
            print("right");
            manageIndent([&]() {
                relativeExpression->getRight()->accept(*this);
            });
        }
        relativeExpression->getPosition();
    });
}

void PrintVisitor::visit(const AdditiveExpression *additiveExpression) {
    if (additiveExpression->getAdditiveType() == AdditiveType::ADD)
        print("add expression");
    else
        print("subtract expression");
    manageIndent([&]() {
        if (additiveExpression->getLeft()) {
            print("left");
            manageIndent([&]() {
                additiveExpression->getLeft()->accept(*this);
            });
        }
        if (additiveExpression->getRight()) {
            print("right");
            manageIndent([&]() {
                additiveExpression->getRight()->accept(*this);
            });
        }
    });
}

void PrintVisitor::visit(const MultiplicationExpression *multiplicationExpression) {
    std::unordered_map<MultiplicativeType, std::string> map = {
            {MultiplicativeType::MULTIPLY, "multiply"},
            {MultiplicativeType::DIVIDE, "divide"},
            {MultiplicativeType::INT_DIVIDE, "int divide"},
            {MultiplicativeType::MODULO, "modulo"},
    };
    print(std::string(map[multiplicationExpression->getMultiplicativeType()]+" expression").c_str());
    manageIndent([&]() {
        if (multiplicationExpression->getLeft()) {
            print("left");
            manageIndent([&]() {
                multiplicationExpression->getLeft()->accept(*this);
            });
        }
        if (multiplicationExpression->getRight()) {
            print("right");
            manageIndent([&]() {
                multiplicationExpression->getRight()->accept(*this);
            });
        }
    });
}

void PrintVisitor::visit(const Constant *constant) {
    std::ostringstream oss;
    if (constant->getConstantType() == ConstantType::INTEGER)
        oss << "integer constant: " << std::get<int>(constant->getValue());
    else if (constant->getConstantType() == ConstantType::FLOAT)
        oss << "float constant: " << std::get<double>(constant->getValue());
    else
        oss << "string constant: " << std::get<std::string>(constant->getValue());
    oss << '\n';
    print(oss.str().c_str());
}

void PrintVisitor::visit(const Field *field) {
    print("field");
    manageIndent([&]() {
        if (field->getFieldType() == FieldType::FIRST)
            print(".first\n");
        else
            print(".second\n");
        print("expression");
        manageIndent([&]() {
            field->getExpression()->accept(*this);
        });
    });
}

void PrintVisitor::visit(const CastExpression *castExpression) {
    print("cast expression");
    manageIndent([&]() {
        print("type");
        manageIndent([&]() {
            if (castExpression->getType() == ConstantType::INTEGER)
                print("integer\n");
            else if (castExpression->getType() == ConstantType::FLOAT)
                print("float\n");
            else
                print("string\n");
        });
        print("expression");
        manageIndent([&]() {
            castExpression->getExpression()->accept(*this);
        });
    });
}

void PrintVisitor::visit(const NegatedExpression *negatedExpression) {
    print("negated expression");
    manageIndent([&]() {
        negatedExpression->getExpression()->accept(*this);
    });
}

void PrintVisitor::visit(const MatchExpression *matchExpression) {
    print("match expression");
    manageIndent([&]() {
        print("expression");
        manageIndent([&]() {
            matchExpression->getExpression()->accept(*this);
        });
        print("identifier");
        manageIndent([&]() {
            matchExpression->getIdentifier()->accept(*this);
        });
        matchExpression->getBlock()->accept(*this);
    });
}

void PrintVisitor::visit(const MatchPair *matchPair) {
    print("match pair");
    manageIndent([&]() {
        print("first");
        manageIndent([&]() {
            matchPair->getFirst()->accept(*this);
        });
        print("second");
        manageIndent([&]() {
            matchPair->getSecond()->accept(*this);
        });
        matchPair->getBlock()->accept(*this);
    });
}

void PrintVisitor::visit(const MatchType *matchType) {
    std::ostringstream oss;
    oss << "match ";
    if (matchType->getConstantType() == ConstantType::INTEGER)
        oss << "integer";
    else if (matchType->getConstantType() == ConstantType::FLOAT)
        oss << "float";
    else
        oss << "string";
    print(oss.str().c_str());
    manageIndent([&]() {
        matchType->getIdentifier()->accept(*this);
        matchType->getBlock()->accept(*this);
    });
}

void PrintVisitor::visit(const MatchNone *matchNone) {
    print("match none");
    manageIndent([&]() {
        matchNone->getBlock()->accept(*this);
    });
}

void PrintVisitor::visit(const Pair *pair) {
    print("pair");
    manageIndent([&]() {
        print("first");
        manageIndent([&]() {
            pair->getFirst()->accept(*this);
        });
        print("second");
        manageIndent([&]() {
            pair->getSecond()->accept(*this);
        });
    });
}

void PrintVisitor::visit(const Typename *type) {
    std::ostringstream oss;
    oss << "Typename ";
    if (type->getType() == ConstantType::INTEGER)
        oss << "Integer";
    else if (type->getType() == ConstantType::FLOAT)
        oss << "Float";
    else
        oss << "String";
    oss << '\n';
    print(oss.str().c_str());
}

void PrintVisitor::print(const char *str) const {
    for (int i = 0; i < indent; i++)
        output << "  ";
    output << str;
}

void PrintVisitor::manageIndent(const std::function<void()>& lambda) {
    output << " {\n";
    indent++;
    lambda();
    indent--;
    print("}\n");
}
