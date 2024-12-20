#include "tokenizer.hpp"

std::string read_keyword(const std::string &input, int &i)
{
	std::string result;

	while (i < input.length() && !isspace(input.at(i))) {
		result.push_back(input.at(i));
		++i;
	}

	return result;
}

std::string read_string(const std::string &input, int &i)
{
	std::string result;
	++i;

	while (i < input.length() && input.at(i) != '"') {
		result.push_back(input.at(i));
		++i;
	}

	if (i < input.length() && input.at(i) == '"') {
		++i;
    }

	return result;
}

std::vector<std::string> tokenize(const std::string &input)
{
	int i { 0 };
	std::vector<std::string> tokens;

	while (i < input.length()) {
		while (i < input.length() && isspace(input.at(i))) ++i;
		if (i >= input.length()) break;

		if (input.at(i) == '"') {
			std::string str = read_string(input, i);
			tokens.push_back(str);
		} else {
			std::string keyword = read_keyword(input, i);
			tokens.push_back(keyword);
		}
	}

	return tokens;
}
