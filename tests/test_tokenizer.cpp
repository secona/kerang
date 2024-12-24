#include <gtest/gtest.h>
#include "tokenizer.hpp"

TEST(SampleTest, TestCase) {
	std::vector<std::string> tokens = tokenize("echo \"Hello, World!\"");
	EXPECT_STREQ(tokens[0].c_str(), "echo");
	EXPECT_STREQ(tokens[1].c_str(), "Hello, World!");
}

