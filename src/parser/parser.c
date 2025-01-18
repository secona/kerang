#include "parser.h"

#include <fcntl.h>
#include <stdlib.h>

Command *parse(Token **cur, Token *end) {
  Command *cmd = (Command *)malloc(sizeof(Command));
  if (!cmd)
    return NULL;

  while (*cur < end) {
    Token *token = *cur;

    switch (token->type) {
    case Word:
      if (cmd->argc < 255) {
        cmd->args[cmd->argc++] = token->value;
      }
      (*cur)++;
      break;

    case Redirection:
      break;

    case Pipe:
      (*cur)++;
      return cmd;

    case EndOfFile:
      return cmd;
    }
  }

  return cmd;
}

Command *parse_commands(TokenArray *arr) {
  if (!arr || !arr->len)
    return NULL;

  Token *cur = arr->tokens;
  Token *end = arr->tokens + arr->len;

  Command *first = NULL;
  Command *current = NULL;

  do {
    Command *cmd = parse(&cur, end);
    if (!cmd)
      return NULL;

    if (!first) {
      first = cmd;
      current = cmd;
    } else {
      current->next = cmd;
      current = cmd;
    }
  } while (cur < end);

  return first;
}
