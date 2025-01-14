#include "parser.hpp"
#include "tokenizer.hpp"

#include <gtest/gtest.h>

TEST(TestParser, SimpleTest) {
  Tokenizer tokenizer("ls -al > out.txt");
  Pipeline pipeline(tokenizer);

  pipeline.parse();

  EXPECT_EQ(pipeline.m_commands.size(), 1);
  EXPECT_STREQ(pipeline.m_commands[0].m_args[0].c_str(), "ls");
  EXPECT_STREQ(pipeline.m_commands[0].m_args[1].c_str(), "-al");
  EXPECT_NE(pipeline.m_commands[0].m_stdout, STDOUT_FILENO);
}
