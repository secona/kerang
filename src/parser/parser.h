#ifndef KERANG_PARSER_PARSER_H_
#define KERANG_PARSER_PARSER_H_

#include "tokenizer.h"

typedef struct {
  const char *args[256];
  int argc;
} Command;

Command *parse(Token *tokens, int count);
Command *parse_commands(TokenArray *arr);

#endif
