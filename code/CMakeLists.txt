cmake_minimum_required(VERSION 3.25)
project(code)

set(CMAKE_CXX_STANDARD 17)
add_subdirectory(tests)

add_executable(code main.cpp TokenType.h Token.h Position.h Lexer.h Token.cpp MyLangLexer.cpp MyLangLexer.h MyLangLexer.h Position.cpp ErrorType.h Error.cpp Error.h)
