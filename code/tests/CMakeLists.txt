set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.24)

enable_testing()
find_package(GTest REQUIRED)
add_executable(Tests_run TestsMain.cpp ../Position.cpp ../MyLangLexer.cpp ../Token.cpp ../MyLangLexer.cpp ../Position.cpp NewLineTest.cpp NumericTokenTest.cpp SimpleTokensTest.cpp IdentifiersAndKeywordsTest.cpp CommentsTest.cpp StringTest.cpp)
target_link_libraries(Tests_run PRIVATE GTest::GTest)
