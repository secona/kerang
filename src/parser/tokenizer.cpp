#include "tokenizer.hpp"

Token::Token(TokenType type, const std::string &value)
  : m_type(type)
  , m_value(value) {
}

Tokenizer::Tokenizer(const std::string &input)
  : m_input(input)
  , m_pos(0) {
}

char Tokenizer::peek() {
  return this->m_pos < this->m_input.size() ? this->m_input[this->m_pos] : 0;
}

char Tokenizer::advance() {
  return this->m_pos < this->m_input.size() ? this->m_input[this->m_pos++] : 0;
}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;

  while (this->m_pos < this->m_input.size()) {
    while (std::isspace(this->peek())) {
      this->advance();
    }

    char current = peek();

    if (current == 0) {
      break;
    }

    if (std::isdigit(current)) {
      this->advance();

      if (this->peek() == '>') {
        this->advance();

        if (this->peek() == '>') {
          this->advance();
          std::string value = ">>";
          value.insert(value.begin(), current);
          tokens.emplace_back(TokenType::Redirection, value);
        } else {
          std::string value = ">";
          value.insert(value.begin(), current);
          tokens.emplace_back(TokenType::Redirection, value);
        }
      }

      continue;
    }

    if (current == '>') {
      this->advance();

      if (this->peek() == '>') {
        this->advance();
        tokens.emplace_back(TokenType::Redirection, ">>");
      } else {
        tokens.emplace_back(TokenType::Redirection, ">");
      }

      continue;
    }

    if (current == '|') {
      this->advance();

      tokens.emplace_back(TokenType::Pipe, "|");

      continue;
    }

    if (current == '"') {
      tokens.emplace_back(this->readQuoted());
      continue;
    }

    tokens.emplace_back(this->readWord());
  }

  return tokens;
}

Token Tokenizer::readQuoted() {
  char quote = this->advance();
  std::string quoted;

  while (this->peek() != quote && this->peek() != 0) {
    quoted += this->advance();
  }

  if (this->peek() == quote) {
    this->advance();
  }

  return Token(TokenType::Word, quoted);
}

Token Tokenizer::readWord() {
  std::string word;

  while (!std::isspace(this->peek()) && this->peek() != 0 &&
         this->peek() != '>' && this->peek() != '|') {
    word += this->advance();
  }

  return Token(TokenType::Word, word);
}
