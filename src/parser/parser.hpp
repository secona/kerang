#ifndef KERANG_PARSER_PARSER_HPP_
#define KERANG_PARSER_PARSER_HPP_

#include "tokenizer.hpp"

#include <string>
#include <unistd.h>
#include <vector>

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

  void parseCommand();
  void parseRedirection();

public:
  std::vector<Command> commands;

  Pipeline(Tokenizer);

  void parse();
};

#endif
