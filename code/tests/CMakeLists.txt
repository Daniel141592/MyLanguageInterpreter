set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.24)

enable_testing()
find_package(GTest REQUIRED)
aux_source_directory(../structure STRUCTURE)
add_executable(Tests_run TestsMain.cpp ../Position.cpp ../lexer/MyLangLexer.cpp ../Token.cpp ../lexer/MyLangLexer.cpp ../Position.cpp lexer/NewLineTest.cpp lexer/NumericTokenTest.cpp lexer/SimpleTokensTest.cpp lexer/IdentifiersAndKeywordsTest.cpp lexer/CommentsTest.cpp lexer/StringTest.cpp ../parser/PrintVisitor.cpp ../parser/PrintVisitor.h ../parser/MyLangParser.cpp ../parser/MyLangParser.h ${STRUCTURE} lexer/GeneralTests.cpp parser/ParserTest.cpp parser/LexerMock/LexerMock.cpp parser/LexerMock/LexerMock.h parser/ParseProgramTest.cpp parser/ParseBlockTest.cpp parser/AssignTest.cpp parser/FunctionCallTest.cpp parser/IfTest.cpp parser/LoopTest.cpp parser/PatternTest.cpp parser/FunctionDeclarationTest.cpp parser/ExpressionTest.cpp parser/RelativeExpressionTest.cpp parser/PairTest.cpp parser/IntegrationWithLexerTest.cpp ../interpreter/Interpreter.h ../interpreter/MyLangInterpreter.cpp ../interpreter/MyLangInterpreter.h ../interpreter/Context.cpp ../interpreter/Context.h ../interpreter/Scope.cpp ../interpreter/Scope.h ../interpreter/Value.cpp ../interpreter/Value.h ../interpreter/Variable.cpp ../structure/StandardOutput.cpp ../structure/StandardOutput.h ../interpreter/MultiplicativeVisitor.cpp ../interpreter/MultiplicativeVisitor.h ../interpreter/AdditiveVisitor.cpp ../interpreter/AdditiveVisitor.h ../interpreter/BooleanVisitor.cpp ../interpreter/BooleanVisitor.h ../interpreter/Exceptions.h ../interpreter/CastVisitor.cpp ../interpreter/CastVisitor.h)
target_link_libraries(Tests_run PRIVATE GTest::GTest)
