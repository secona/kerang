#ifndef KERANG_PARSER_PARSER_H_
#define KERANG_PARSER_PARSER_H_

#include "tokenizer.h"

typedef struct command {
    const char *args[256];
    int argc;

    struct command *next;
} Command;

Command *parse_commands(Tokenizer *tokenizer);

#endif
