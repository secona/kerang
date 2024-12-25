#include <gtest/gtest.h>
#include "tokenizer.hpp"

TEST(TokenizerTests, TestWordsAndQuotes) {
	Tokenizer tokenizer("echo \"Hello, World!\"");
	std::vector<Token> tokens = tokenizer.tokenize();

	EXPECT_EQ(tokens[0].type, TokenType::Word);
	EXPECT_STREQ(tokens[0].value.c_str(), "echo");

	EXPECT_EQ(tokens[1].type, TokenType::Word);
	EXPECT_STREQ(tokens[1].value.c_str(), "Hello, World!");
}

TEST(TokenizerTests, TestOutputRedirect) {
	Tokenizer tokenizer("ls -al >> test.txt");
	std::vector<Token> tokens = tokenizer.tokenize();

	EXPECT_EQ(tokens[0].type, TokenType::Word);
	EXPECT_STREQ(tokens[0].value.c_str(), "ls");

	EXPECT_EQ(tokens[1].type, TokenType::Word);
	EXPECT_STREQ(tokens[1].value.c_str(), "-al");

	EXPECT_EQ(tokens[2].type, TokenType::Redirection);
	EXPECT_STREQ(tokens[2].value.c_str(), ">>");

	EXPECT_EQ(tokens[3].type, TokenType::Word);
	EXPECT_STREQ(tokens[3].value.c_str(), "test.txt");
}

TEST(TokenizerTests, TestPipe) {
	Tokenizer tokenizer("ls -al | grep main.cpp");
	std::vector<Token> tokens = tokenizer.tokenize();

	EXPECT_EQ(tokens[0].type, TokenType::Word);
	EXPECT_STREQ(tokens[0].value.c_str(), "ls");

	EXPECT_EQ(tokens[1].type, TokenType::Word);
	EXPECT_STREQ(tokens[1].value.c_str(), "-al");

	EXPECT_EQ(tokens[2].type, TokenType::Pipe);
	EXPECT_STREQ(tokens[2].value.c_str(), "|");

	EXPECT_EQ(tokens[3].type, TokenType::Word);
	EXPECT_STREQ(tokens[3].value.c_str(), "grep");

	EXPECT_EQ(tokens[4].type, TokenType::Word);
	EXPECT_STREQ(tokens[4].value.c_str(), "main.cpp");
}
