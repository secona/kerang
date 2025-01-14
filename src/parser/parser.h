#ifndef KERANG_PARSER_PARSER_H_
#define KERANG_PARSER_PARSER_H_

#include "tokenizer.h"

#include <unistd.h>

typedef struct {
  int in_fd;
  int out_fd;
  int err_fd;

  const char **args;
  int argc;
} Command;

Command *parse(Token *tokens, int count);

#endif
