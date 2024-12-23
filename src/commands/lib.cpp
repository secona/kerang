#include "lib.hpp"

int CommandManager::execute_command(const std::vector<std::string> &args)
{
	if (this->commands.find(args[0]) != commands.end()) {
		return this->commands[args[0]]->execute_command(args);
	}

	return NOT_FOUND;
}

CommandManager::CommandManager()
{
	this->commands["exit"] = std::make_unique<ExitCommand>();
	this->commands["cd"] = std::make_unique<ChangeDirectoryCommand>();
}

