#include <gtest/gtest.h>

#include "parser.hpp"
#include "tokenizer.hpp"

TEST(TestParser, SimpleTest) {
    Tokenizer tokenizer("ls -al > out.txt");
    Pipeline pipeline(tokenizer);

    pipeline.parse();

    EXPECT_EQ(pipeline.commands.size(), 1);
    EXPECT_STREQ(pipeline.commands[0].args[0].c_str(), "ls");
    EXPECT_STREQ(pipeline.commands[0].args[1].c_str(), "-al");
    EXPECT_NE(pipeline.commands[0].stdout, STDOUT_FILENO);
}
