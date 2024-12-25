#include <gtest/gtest.h>
#include "tokenizer.hpp"

TEST(SampleTest, TestCase) {
	Tokenizer tokenizer("echo \"Hello, World!\"");
	std::vector<Token> tokens = tokenizer.tokenize();

	EXPECT_EQ(tokens[0].type, TokenType::Word);
	EXPECT_STREQ(tokens[0].value.c_str(), "echo");

	EXPECT_EQ(tokens[1].type, TokenType::Word);
	EXPECT_STREQ(tokens[1].value.c_str(), "Hello, World!");
}

