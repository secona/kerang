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

CommandManager::CommandManager()
{
	this->commands["exit"] = std::make_unique<ExitCommand>();
	this->commands["cd"] = std::make_unique<ChangeDirectoryCommand>();
}

int CommandManager::execute_command(const std::vector<std::string> &args)
{
	if (this->commands.find(args[0]) != commands.end()) {
		return this->commands[args[0]]->execute_command(args);
	}

	return NOT_FOUND;
}
