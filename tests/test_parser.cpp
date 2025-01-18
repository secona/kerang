extern "C" {
#include "parser.h"
#include "tokenizer.h"
}

#include <gtest/gtest.h>

TEST(ParserTest, HandlesBasic) {
  const char *input = "ls";

  Tokenizer tokenizer = Tokenizer_new(input);
  Command *commands = parse_commands(&tokenizer);

  EXPECT_EQ(commands->argc, 1);
  EXPECT_STREQ(commands->args[0], "ls");
}

TEST(ParserTest, HandlesMultiple) {
  const char *input = "ls | grep test.txt";

  Tokenizer tokenizer = Tokenizer_new(input);
  Command *commands = parse_commands(&tokenizer);

  EXPECT_EQ(commands->argc, 1);
  EXPECT_STREQ(commands->args[0], "ls");

  EXPECT_EQ(commands->next->argc, 2);
  EXPECT_STREQ(commands->next->args[0], "grep");
  EXPECT_STREQ(commands->next->args[1], "test.txt");
}
