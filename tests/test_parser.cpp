extern "C" {
#include "parser.h"
#include "tokenizer.h"
}

#include <gtest/gtest.h>

TEST(ParserTest, HandlesBasic) {
  const char *input = "ls";

  TokenArray *arr = tokenize(input);
  Command *commands = parse_commands(arr);

  EXPECT_EQ(commands[0].argc, 1);
  EXPECT_STREQ(commands[0].args[0], "ls");
}
