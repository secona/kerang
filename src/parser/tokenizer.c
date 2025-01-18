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
        token.type = Empty;
        token.value = NULL;
        return token;
    }

    while (isspace(*tokenizer->ptr))
        tokenizer->ptr++;

    const char *start = tokenizer->ptr;

    if (isdigit(*tokenizer->ptr)) {
        tokenizer->ptr++;

        if (*tokenizer->ptr == '>') {
            tokenizer->ptr++;

            if (*tokenizer->ptr == '>') tokenizer->ptr++;

            token.type = Redirection;
            token.value = malloc(tokenizer->ptr - start + 1);
            memcpy(token.value, start, tokenizer->ptr - start);
            return token;
        }
    }

    if (*tokenizer->ptr == '>') {
        tokenizer->ptr++;

        if (*tokenizer->ptr == '>') tokenizer->ptr++;

        token.type = Redirection;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);

        return token;
    }

    if (*tokenizer->ptr == '|') {
        tokenizer->ptr++;

        token.type = Pipe;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);

        return token;
    }

    if (*tokenizer->ptr == '"') {
        start++;
        tokenizer->ptr++;

        while (!(*tokenizer->ptr == '"' || *tokenizer->ptr == 0))
            tokenizer->ptr++;

        token.type = Word;
        token.value = malloc(tokenizer->ptr - start + 1);
        memcpy(token.value, start, tokenizer->ptr - start);

        tokenizer->ptr++;

        return token;
    }

    while (!isspace(*tokenizer->ptr) && *tokenizer->ptr != 0 && *tokenizer->ptr != '>' && *tokenizer->ptr != '|')
        tokenizer->ptr++;

    token.type = Word;
    token.value = malloc(tokenizer->ptr - start + 1);
    memcpy(token.value, start, tokenizer->ptr - start);
    return token;
}
