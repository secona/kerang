#include "parser.h"

#include <fcntl.h>
#include <stdlib.h>

Command *parse_commands(Tokenizer *tokenizer) {
    Command *current = (Command *)malloc(sizeof(Command));
    Command *first = current;

    while (1) {
        Token token = Tokenizer_next(tokenizer);

        switch (token.type) {
        case Word:
            if (current->argc < 255) {
                current->args[current->argc++] = token.value;
            }
            break;

        case Redirection:
            break;

        case Pipe:
            current->next = (Command *)malloc(sizeof(Command));
            current = current->next;
            break;

        case Empty:
        case EndOfFile:
            return first;
        }
    }
}
