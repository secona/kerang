#include "parser.h"

#include "tokenizer.h"

#include <fcntl.h>
#include <stdlib.h>

Command default_command() {
  Command cmd = {
    .in_fd = STDIN_FILENO,
    .out_fd = STDOUT_FILENO,
    .err_fd = STDERR_FILENO,

    .args = (const char **)malloc(sizeof(char *) * 3),
    .argc = 0,
  };

  return cmd;
}

/*
 * NOTE: parse currently cannot handle multiple arguments. I goofed up
 * when defining the `value` property of Token. Because it is a pointer,
 * it doesn't have a NULL terminator, and so the first argument is just
 * the whole string that the user inputs in. Future me, don't forget to
 * fix this up!
 */

Command *parse(Token *tokens, int count) {
  int capacity = 10;
  Command *cmd = (Command *)malloc(sizeof(Command) * capacity);

  int cmd_i = 0;
  cmd[cmd_i] = default_command();

  for (int i = 0; i < count; i++) {
    switch (tokens[i].type) {
    case Word:
      cmd[cmd_i].args[cmd->argc++] = tokens[i].value;

    case Redirection:
    case Pipe:
    case EndOfFile:;
    }
  }

  return cmd;
}
