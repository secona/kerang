#include "parser.h"

#include <fcntl.h>
#include <stdlib.h>

Command *parse(Token *tokens, int count) {
  Command *cmd = (Command *)malloc(sizeof(Command));
  if (!cmd)
    return NULL;

  for (int i = 0; i < count; i++) {
    switch (tokens[i].type) {
    case Word:
      if (cmd->argc < 255) {
        cmd->args[cmd->argc++] = tokens[i].value;
      }

    case Redirection:
    case Pipe:
    case EndOfFile:;
    }
  }

  return cmd;
}

Command *parse_commands(TokenArray *arr) {
  if (!arr || !arr->len)
    return NULL;

  Command *first = parse(arr->tokens, arr->len);
  if (!first)
    return NULL;

  return first;
}
