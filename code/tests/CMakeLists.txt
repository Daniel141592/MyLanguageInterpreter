set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.24)

enable_testing()
find_package(GTest REQUIRED)
aux_source_directory(../parser/structure STRUCTURE)
add_executable(Tests_run TestsMain.cpp ../Position.cpp ../lexer/MyLangLexer.cpp ../Token.cpp ../lexer/MyLangLexer.cpp ../Position.cpp NewLineTest.cpp NumericTokenTest.cpp SimpleTokensTest.cpp IdentifiersAndKeywordsTest.cpp CommentsTest.cpp StringTest.cpp ../parser/structure/Program.cpp ../parser/structure/Program.h ../parser/structure/Declaration.h ../parser/structure/Assign.cpp ../parser/structure/Assign.h ../parser/structure/OrExpression.h ../parser/structure/Instruction.h ../parser/structure/SingleInstruction.h ../parser/PrintVisitor.cpp ../parser/PrintVisitor.h ../parser/MyLangParser.cpp ../parser/MyLangParser.h ${STRUCTURE})
target_link_libraries(Tests_run PRIVATE GTest::GTest)
