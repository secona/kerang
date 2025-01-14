#include "lib.hpp"

#include "tokenizer.hpp"

#include <sstream>

std::vector<std::string> parseInput(const std::string &input) {
  Tokenizer tokenizer(input);
  std::vector<Token> tokens = tokenizer.tokenize();

  std::vector<std::string> tokensString;
  for (Token token : tokens) {
    tokensString.push_back(token.value);
  }

  return tokensString;
}
