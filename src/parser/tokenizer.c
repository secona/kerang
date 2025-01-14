#include "tokenizer.h"

#include <ctype.h>

Token *tokenize(const char *input, int *count) {
  int capacity = 10;
  Token *tokens = (Token *)malloc(sizeof(Token) * capacity);

  const char *ptr = input;
  const char *start = input;

  while (*ptr != 0) {
    if (*count >= capacity) {
      capacity *= 2;
      tokens = (Token *)realloc(tokens, sizeof(Token) * capacity);
    }

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

        tokens[*count].type = Redirection;
        tokens[*count].len = ptr - start;
        tokens[*count].value = start;

        (*count)++;
      }

      continue;
    }

    if (*ptr == '>') {
      ptr++;

      if (*ptr == '>')
        ptr++;

      tokens[*count].type = Redirection;
      tokens[*count].len = ptr - start;
      tokens[*count].value = start;

      (*count)++;

      continue;
    }

    if (*ptr == '|') {
      ptr++;

      tokens[*count].type = Pipe;
      tokens[*count].len = ptr - start;
      tokens[*count].value = start;

      (*count)++;

      continue;
    }

    if (*ptr == '"') {
      start++;
      ptr++;

      while (!(*ptr == '"' || *ptr == 0))
        ptr++;

      tokens[*count].type = Word;
      tokens[*count].len = ptr - start;
      tokens[*count].value = start;

      (*count)++;

      continue;
    }

    while (!(isspace(*ptr) || *ptr == 0 || *ptr == '>' || *ptr == '|'))
      ptr++;

    tokens[*count].type = Word;
    tokens[*count].len = ptr - start;
    tokens[*count].value = start;

    (*count)++;
  }

  return tokens;
}
