#include "tokenizer.hpp"

Token::Token(TokenType type, const std::string &value)
  : type(type)
  , value(value) {
}

Tokenizer::Tokenizer(const std::string &input)
  : input(input)
  , pos(0) {
}

char Tokenizer::peek() {
  return this->pos < this->input.size() ? this->input[this->pos] : 0;
}

char Tokenizer::advance() {
  return this->pos < this->input.size() ? this->input[this->pos++] : 0;
}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;

  while (this->pos < this->input.size()) {
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
      tokens.emplace_back(this->read_quoted());
      continue;
    }

    tokens.emplace_back(this->read_word());
  }

  return tokens;
}

Token Tokenizer::read_quoted() {
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

Token Tokenizer::read_word() {
  std::string word;

  while (!std::isspace(this->peek()) && this->peek() != 0 &&
         this->peek() != '>' && this->peek() != '|') {
    word += this->advance();
  }

  return Token(TokenType::Word, word);
}
