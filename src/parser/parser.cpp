#include "parser.hpp"

#include <fcntl.h>
#include <iostream>

Command::Command()
  : stdin(STDIN_FILENO)
  , stdout(STDOUT_FILENO)
  , stderr(STDERR_FILENO) {
}

Pipeline::Pipeline(Tokenizer tokenizer)
  : pos(0)
  , tokens(tokenizer.tokenize()) {
}

Token *Pipeline::peek() {
  return this->pos < this->tokens.size() ? &this->tokens[this->pos] : NULL;
}

Token *Pipeline::advance() {
  return this->pos < this->tokens.size() ? &this->tokens[this->pos++] : NULL;
}

void Pipeline::parse() {
  while (pos < tokens.size()) {
    Token *current = peek();

    if (current->type == TokenType::Word) {
      parse_command();
    }

    if (current->type == TokenType::Redirection) {
      parse_redirection();
    }
  }
}

void Pipeline::parse_command() {
  Command command;

  command.args.emplace_back(advance()->value);

  while (peek()->type == TokenType::Word) {
    command.args.emplace_back(advance()->value);
  }

  commands.emplace_back(command);
}

void Pipeline::parse_redirection() {
  if (commands.size() == 0) {
    return;
  }

  Command &command = commands.back();

  Token *token = advance();

  if (token->value == ">") {
    command.stdout = open(advance()->value.c_str(), O_CREAT | O_WRONLY, 0666);
  }
}
