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
  char *value;
} Token;

typedef struct {
  Token *tokens;
  size_t cap;
  size_t len;
} TokenArray;

TokenArray *tokenize(const char *input);

#endif
