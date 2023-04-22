set(CMAKE_CXX_STANDARD 17)

cmake_minimum_required(VERSION 3.25)

enable_testing()
find_package(GTest REQUIRED)
add_executable(Tests_run TestsMain.cpp ../Position.cpp ../MyLangLexer.cpp ../Token.cpp ../MyLangLexer.cpp ../Position.cpp)
target_link_libraries(Tests_run PRIVATE GTest::GTest)
