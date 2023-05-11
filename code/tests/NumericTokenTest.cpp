#include <gtest/gtest.h>
#include <climits>

#include "../lexer/MyLangLexer.h"

TEST(NumericTokenTest, BuildSimpleInt) {
    std::istringstream iss("1234");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    int value = std::get<int>(token.getValue());
    ASSERT_EQ(value, 1234);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildZero) {
    std::istringstream iss("0");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    int value = std::get<int>(token.getValue());
    ASSERT_EQ(value, 0);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildIntOverMaxRange) {
    std::stringstream stream;
    stream << std::numeric_limits<int>::max() << "0";    // stream contains value 10 times greater than std::numeric_limits<int>::max()
    bool errorOccurred = false;
    bool intOverflow = false;
    MyLangLexer lexer(stream, [&errorOccurred, &intOverflow](Position p, ErrorType e){
        intOverflow = e == ErrorType::IntRangeError;
        errorOccurred = e != ErrorType::IntRangeError;
    });
    lexer.nextToken();
    ASSERT_TRUE(intOverflow);
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildMultipleInteters) {
    std::istringstream iss("1234 89234 123423");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    int values[3];
    Position positions[3];
    for (int i = 0; i < 3; ++i) {
        values[i] = std::get<int>(token.getValue());
        positions[i] = token.getPosition();
        token = *lexer.nextToken();
    }
    ASSERT_EQ(values[0], 1234);
    ASSERT_TRUE(positions[0] == Position(1, 1));
    ASSERT_EQ(values[1], 89234);
    ASSERT_TRUE(positions[1] == Position(6, 1));
    ASSERT_EQ(values[2], 123423);
    ASSERT_TRUE(positions[2] == Position(12, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildIntAfterOperator) {
    std::istringstream iss("-1234");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    ASSERT_EQ(token.getType(), TokenType::MINUS);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    token = *lexer.nextToken();
    int value = std::get<int>(token.getValue());
    ASSERT_EQ(value, 1234);
    ASSERT_TRUE(token.getPosition() == Position(2, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildSimpleFloat) {
    std::istringstream iss("1234.5678");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    double value = std::get<double>(token.getValue());
    ASSERT_EQ(value, 1234.5678);
    ASSERT_TRUE(token.getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildMultipleFloats) {
    std::istringstream iss("12.34 892.34 123.423");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    Token token = *lexer.nextToken();
    double values[3];
    Position positions[3];
    for (int i = 0; i < 3; ++i) {
        values[i] = std::get<double>(token.getValue());
        positions[i] = token.getPosition();
        token = *lexer.nextToken();
    }
    ASSERT_EQ(values[0], 12.34);
    ASSERT_TRUE(positions[0] == Position(1, 1));
    ASSERT_EQ(values[1], 892.34);
    ASSERT_TRUE(positions[1] == Position(7, 1));
    ASSERT_EQ(values[2], 123.423);
    ASSERT_TRUE(positions[2] == Position(14, 1));
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildFloatWithIntegerPartOverRange) {
    std::stringstream stream;
    stream << std::numeric_limits<int>::max() << "0.1234";    // stream contains value 10 times greater than std::numeric_limits<int>::max()
    bool errorOccurred = false;
    bool intOverflow = false;
    MyLangLexer lexer(stream, [&errorOccurred, &intOverflow](Position p, ErrorType e){
        intOverflow = e == ErrorType::IntRangeError;
        errorOccurred = e != ErrorType::IntRangeError;
    });
    lexer.nextToken();
    ASSERT_TRUE(intOverflow);
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildFloatWithDecimalPartOverRange) {
    std::stringstream stream;
    stream << "1234." << std::numeric_limits<int>::max();    // stream contains value 10 times greater than std::numeric_limits<int>::max()
    bool errorOccurred = false;
    bool intOverflow = false;
    MyLangLexer lexer(stream, [&errorOccurred, &intOverflow](Position p, ErrorType e){
        intOverflow = e == ErrorType::IntRangeError;
        errorOccurred = e != ErrorType::IntRangeError;
    });
    lexer.nextToken();
    ASSERT_TRUE(intOverflow);
    ASSERT_FALSE(errorOccurred);
}

TEST(NumericTokenTest, BuildFloatWithUnexpectEOTAfterComma) {
    std::istringstream iss("1234.");
    bool errorOccurred = false;
    bool unexpectedEOT = false;
    MyLangLexer lexer(iss, [&errorOccurred, &unexpectedEOT](Position p, ErrorType e){
        unexpectedEOT = e == ErrorType::IncorrectFloatValue;
        errorOccurred = e != ErrorType::IncorrectFloatValue;
    });
    Token token = *lexer.nextToken();
    ASSERT_TRUE(unexpectedEOT);
    ASSERT_FALSE(errorOccurred);
    double value = std::get<double>(token.getValue());
    ASSERT_EQ(value, 1234.0);
}
