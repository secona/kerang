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
  return m_pos < m_input.size() ? m_input[m_pos] : 0;
}

char Tokenizer::advance() {
  return m_pos < m_input.size() ? m_input[m_pos++] : 0;
}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;

  while (m_pos < m_input.size()) {
    while (std::isspace(peek())) {
      advance();
    }

    char current = peek();

    if (current == 0) {
      break;
    }

    if (std::isdigit(current)) {
      advance();

      if (peek() == '>') {
        advance();

        if (peek() == '>') {
          advance();
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
      advance();

      if (peek() == '>') {
        advance();
        tokens.emplace_back(TokenType::Redirection, ">>");
      } else {
        tokens.emplace_back(TokenType::Redirection, ">");
      }

      continue;
    }

    if (current == '|') {
      advance();

      tokens.emplace_back(TokenType::Pipe, "|");

      continue;
    }

    if (current == '"') {
      tokens.emplace_back(readQuoted());
      continue;
    }

    tokens.emplace_back(readWord());
  }

  return tokens;
}

Token Tokenizer::readQuoted() {
  char quote = advance();
  std::string quoted;

  while (peek() != quote && peek() != 0) {
    quoted += advance();
  }

  if (peek() == quote) {
    advance();
  }

  return Token(TokenType::Word, quoted);
}

Token Tokenizer::readWord() {
  std::string word;

  while (!std::isspace(peek()) && peek() != 0 &&
         peek() != '>' && peek() != '|') {
    word += advance();
  }

  return Token(TokenType::Word, word);
}
