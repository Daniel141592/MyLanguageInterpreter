cmake_minimum_required(VERSION 3.24)
project(code)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(tests)

add_executable(code main.cpp TokenType.h Token.h Position.h lexer/Lexer.h Token.cpp lexer/MyLangLexer.cpp lexer/MyLangLexer.h lexer/MyLangLexer.h Position.cpp lexer/ErrorType.h print_utils.cpp print_utils.h lexer/LexerWithoutComments.cpp lexer/LexerWithoutComments.h parser/Visitor.h parser/structure/Program.cpp parser/structure/Program.h parser/Visitable.h parser/structure/Block.cpp parser/structure/Block.h parser/structure/Declaration.h parser/structure/Assign.cpp parser/structure/Assign.h parser/structure/Expression.h parser/structure/Instruction.h parser/structure/SingleInstruction.h parser/PrintVisitor.cpp parser/PrintVisitor.h parser/structure/VariableDeclaration.cpp parser/structure/VariableDeclaration.h parser/structure/Identifier.cpp parser/structure/Identifier.h parser/structure/Expression.cpp parser/structure/FunctionDeclaration.cpp parser/structure/FunctionDeclaration.h parser/structure/Argument.cpp parser/structure/Argument.h)
