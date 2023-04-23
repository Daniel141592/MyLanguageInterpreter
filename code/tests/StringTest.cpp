#include <gtest/gtest.h>

#include "../MyLangLexer.h"

TEST(StringTest, BuildSimpleString) {
    std::istringstream iss("\"some value\"");
    bool errorOccurred = false;
    MyLangLexer lexer(iss, [&errorOccurred](Position p, ErrorType e){ errorOccurred = true;});
    lexer.nextToken();
    std::string value = std::get<std::string>(lexer.getToken().getValue());
    ASSERT_EQ(lexer.getToken().getType(), TokenType::STRING_LITERAL);
    ASSERT_EQ(value, "some value");
    ASSERT_TRUE(lexer.getToken().getPosition() == Position(1, 1));
    ASSERT_FALSE(errorOccurred);
}
