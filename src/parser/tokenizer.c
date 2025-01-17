#include "tokenizer.h"

#include <ctype.h>

TokenArray *create_token_array(size_t capacity) {
  TokenArray *arr = (TokenArray *)malloc(sizeof(TokenArray));
  if (!arr)
    return NULL;

  arr->tokens = malloc(sizeof(Token) * capacity);
  if (!arr->tokens) {
    return NULL;
    free(arr);
  }

  arr->cap = capacity;
  arr->len = 0;

  return arr;
}

void expand_token_array(TokenArray *arr) {
  size_t new_cap = arr->cap * 2;
  Token *new_tokens = (Token *)realloc(arr->tokens, sizeof(Token) * new_cap);

  arr->cap = new_cap;
  arr->tokens = new_tokens;
}

void add_token(TokenArray *arr, TokenType type, const char *value, size_t len) {
  if (arr->len >= arr->cap) {
    expand_token_array(arr);
  }

  arr->tokens[arr->len].type = type;
  arr->tokens[arr->len].value = value;
  arr->tokens[arr->len].len = len;
  arr->len++;
}

TokenArray *tokenize(const char *input) {
  int capacity = 10;
  TokenArray *arr = create_token_array(10);

  const char *ptr = input;
  const char *start = input;

  while (*ptr != 0) {
    if (isspace(*ptr)) {
      ptr++;
      continue;
    }

    start = ptr;

    if (isdigit(*ptr)) {
      ptr++;

      if (*ptr == '>') {
        ptr++;

        if (*ptr == '>')
          ptr++;

        add_token(arr, Redirection, start, ptr - start);
      }

      continue;
    }

    if (*ptr == '>') {
      ptr++;

      if (*ptr == '>')
        ptr++;

      add_token(arr, Redirection, start, ptr - start);

      continue;
    }

    if (*ptr == '|') {
      ptr++;

      add_token(arr, Pipe, start, ptr - start);

      continue;
    }

    if (*ptr == '"') {
      start++;
      ptr++;

      while (!(*ptr == '"' || *ptr == 0))
        ptr++;

      add_token(arr, Word, start, ptr - start);

      continue;
    }

    while (!(isspace(*ptr) || *ptr == 0 || *ptr == '>' || *ptr == '|'))
      ptr++;

    add_token(arr, Word, start, ptr - start);
  }

  return arr;
}
