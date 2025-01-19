#include "parser.h"

#include <fcntl.h>
#include <stdlib.h>

Command *parse_commands(Tokenizer *tokenizer) {
    Command *current = (Command *)malloc(sizeof(Command));
    Command *first = current;

    while (1) {
        Token token = Tokenizer_next(tokenizer);

        switch (token.type) {
        case TOKEN_WORD:
            if (current->argc < 255) {
                current->args[current->argc++] = token.value;
            }
            break;

        case TOKEN_REDIR:
            break;

        case TOKEN_PIPE:
        case TOKEN_SEMICOLON:
        case TOKEN_NEWLINE:
        case TOKEN_EOF:
            current->next = (Command *)malloc(sizeof(Command));
            current = current->next;
            break;

        case TOKEN_EMPTY:
            return first;
        }
    }
}
