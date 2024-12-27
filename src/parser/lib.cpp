#include "lib.hpp"

#include <sstream>

#include "tokenizer.hpp"

std::vector<std::string> parse_input(const std::string &input) {
    Tokenizer tokenizer(input);
    std::vector<Token> tokens = tokenizer.tokenize();

    std::vector<std::string> tokens_str;
    for (Token token : tokens) {
        tokens_str.push_back(token.value);
    }

    return tokens_str;
}
