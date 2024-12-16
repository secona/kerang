#include <sstream>

#include "parser.hpp"

void parse_input(const std::string &input, std::vector<std::string> &args)
{
	std::istringstream stream(input);
	std::string token;
	while (stream >> token) {
		args.push_back(token);
	}
}

