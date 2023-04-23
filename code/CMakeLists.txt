cmake_minimum_required(VERSION 3.24)
project(code)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(tests)

add_executable(code main.cpp TokenType.h Token.h Position.h Lexer.h Token.cpp MyLangLexer.cpp MyLangLexer.h MyLangLexer.h Position.cpp ErrorType.h print_utils.cpp print_utils.h LexerWithoutComments.cpp LexerWithoutComments.h)
