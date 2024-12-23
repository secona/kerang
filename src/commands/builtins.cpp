#include "builtins.hpp"

int ExitCommand::execute_command(const std::vector<std::string> &args)
{
	return SHOULD_EXIT;
}

int ChangeDirectoryCommand::execute_command(const std::vector<std::string> &args)
{
	std::string path = args[1].c_str();

	if (chdir(args[1].c_str()) != 0) {
		std::cerr << strerror(errno) << " (error: " << errno << ")" << std::endl;
	}

	return OK;
}
