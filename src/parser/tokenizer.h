#ifndef KERANG_PARSER_TOKENIZER_H_
#define KERANG_PARSER_TOKENIZER_H_

#include <stdlib.h>

typedef enum {
  Word,
  Redirection,
  Pipe,
  EndOfFile,
} TokenType;

typedef struct {
  TokenType type;
  const char *value;
  size_t len;
} Token;

Token *tokenize(const char *input, int *count);

#endif
