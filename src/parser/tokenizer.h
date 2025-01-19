#ifndef KERANG_PARSER_TOKENIZER_H_
#define KERANG_PARSER_TOKENIZER_H_

#include <stdlib.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_REDIR,
    TOKEN_PIPE,
    TOKEN_EOF,
    TOKEN_EMPTY,
    TOKEN_SEMICOLON,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

typedef struct {
    const char *input;
    const char *ptr;
} Tokenizer;

Token Tokenizer_next(Tokenizer *tokenizer);
Tokenizer Tokenizer_new(const char *input);

#endif
