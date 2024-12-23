#include <sstream>

#include "lib.hpp"
#include "tokenizer.hpp"

std::vector<std::string> parse_input(const std::string &input)
{
	return tokenize(input);
}

