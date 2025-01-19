#include "tokenizer.h"

#include <ctype.h>
#include <string.h>

Tokenizer Tokenizer_new(const char *input) {
    Tokenizer tokenizer;
    tokenizer.input = input;
    tokenizer.ptr = input;

    return tokenizer;
}

Token Tokenizer_next(Tokenizer *tokenizer) {
    Token token;

    if (!tokenizer || *tokenizer->ptr == 0) {
        token.type = TOKEN_EMPTY;
        token.value = NULL;
        return token;
    }

    while (isspace(*tokenizer->ptr))
        tokenizer->ptr++;

    const char *start = tokenizer->ptr;

    if (*tokenizer->ptr == ';') {
        tokenizer->ptr++;

        token.type = TOKEN_SEMICOLON;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);
        return token;
    }

    if (isdigit(*tokenizer->ptr)) {
        tokenizer->ptr++;

        if (*tokenizer->ptr == '>') {
            tokenizer->ptr++;

            if (*tokenizer->ptr == '>') tokenizer->ptr++;

            token.type = TOKEN_REDIR;
            token.value = malloc(tokenizer->ptr - start + 1);
            memcpy(token.value, start, tokenizer->ptr - start);
            return token;
        }
    }

    if (*tokenizer->ptr == '>') {
        tokenizer->ptr++;

        if (*tokenizer->ptr == '>') tokenizer->ptr++;

        token.type = TOKEN_REDIR;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);

        return token;
    }

    if (*tokenizer->ptr == '|') {
        tokenizer->ptr++;

        token.type = TOKEN_PIPE;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);

        return token;
    }

    if (*tokenizer->ptr == '"') {
        start++;
        tokenizer->ptr++;

        while (!(*tokenizer->ptr == '"' || *tokenizer->ptr == 0))
            tokenizer->ptr++;

        token.type = TOKEN_WORD;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);

        tokenizer->ptr++;

        return token;
    }

    while (!isspace(*tokenizer->ptr) && *tokenizer->ptr != 0 && *tokenizer->ptr != '>' && *tokenizer->ptr != '|')
        tokenizer->ptr++;

    token.type = TOKEN_WORD;
    token.value = malloc(tokenizer->ptr - start + 1);
    memcpy(token.value, start, tokenizer->ptr - start);
    return token;
}
