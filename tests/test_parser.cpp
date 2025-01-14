extern "C" {
#include "parser.h"
#include "tokenizer.h"
}

#include <gtest/gtest.h>

TEST(ParserTest, HandlesBasic) {
  const char *input = "ls";
  int count = 0;

  Token *tokens = tokenize(input, &count);
  Command *commands = parse(tokens, count);

  EXPECT_EQ(commands[0].argc, 1);
  EXPECT_STREQ(commands[0].args[0], "ls");
}
