#include "parser.hpp"

#include <fcntl.h>
#include <iostream>

Command::Command()
  : m_stdin(STDIN_FILENO)
  , m_stdout(STDOUT_FILENO)
  , m_stderr(STDERR_FILENO) {
}

Pipeline::Pipeline(Tokenizer tokenizer)
  : m_pos(0)
  , m_tokens(tokenizer.tokenize()) {
}

Token *Pipeline::peek() {
  return this->m_pos < this->m_tokens.size() ? &this->m_tokens[this->m_pos] : NULL;
}

Token *Pipeline::advance() {
  return this->m_pos < this->m_tokens.size() ? &this->m_tokens[this->m_pos++] : NULL;
}

void Pipeline::parse() {
  while (m_pos < m_tokens.size()) {
    Token *current = peek();

    if (current->m_type == TokenType::Word) {
      parseCommand();
    }

    if (current->m_type == TokenType::Redirection) {
      parseRedirection();
    }
  }
}

void Pipeline::parseCommand() {
  Command command;

  command.m_args.emplace_back(advance()->m_value);

  while (peek()->m_type == TokenType::Word) {
    command.m_args.emplace_back(advance()->m_value);
  }

  m_commands.emplace_back(command);
}

void Pipeline::parseRedirection() {
  if (m_commands.size() == 0) {
    return;
  }

  Command &command = m_commands.back();

  Token *token = advance();

  if (token->m_value == ">") {
    command.m_stdout = open(advance()->m_value.c_str(), O_CREAT | O_WRONLY, 0666);
  }
}
