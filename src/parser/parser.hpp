#ifndef KERANG_PARSER_PARSER_HPP_
#define KERANG_PARSER_PARSER_HPP_

#include "tokenizer.hpp"

#include <string>
#include <unistd.h>
#include <vector>

class Command {
public:
  std::vector<std::string> m_args;

  int m_stdin;
  int m_stdout;
  int m_stderr;

  Command();
};

class Pipeline {
private:
  int m_pos;
  std::vector<Token> m_tokens;

  Token *peek();
  Token *advance();

  void parseCommand();
  void parseRedirection();

public:
  std::vector<Command> m_commands;

  Pipeline(Tokenizer);

  void parse();
};

#endif
