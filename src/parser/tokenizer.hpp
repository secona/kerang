#ifndef KERANG_PARSER_TOKENIZER_HPP_
#define KERANG_PARSER_TOKENIZER_HPP_

#include <string>
#include <vector>

enum TokenType {
  Word,
  Redirection,
  Pipe,
  EndOfFile
};

class Token {
public:
  TokenType m_type;
  std::string m_value;

  Token(TokenType type, const std::string &value);
};

class Tokenizer {
  std::string m_input;
  size_t m_pos;

public:
  Tokenizer(const std::string &input);
  std::vector<Token> tokenize();

private:
  char peek();
  char advance();

  Token readQuoted();
  Token readWord();
};

#endif
