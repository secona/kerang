#ifndef KERANG_PARSER_PARSER_HPP_
#define KERANG_PARSER_PARSER_HPP_

#include <unistd.h>

#include <string>
#include <vector>

#include "tokenizer.hpp"

class Command {
public:
    std::vector<std::string> args;

    int stdin;
    int stdout;
    int stderr;

    Command();
};

class Pipeline {
private:
    int pos;
    std::vector<Token> tokens;

    Token *peek();
    Token *advance();

    void parse_command();
    void parse_redirection();

public:
    std::vector<Command> commands;

    Pipeline(Tokenizer);

    void parse();
};

#endif
