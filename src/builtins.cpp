#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <memory>
#include "builtins.hpp"

int ExitCommand::execute_command(const std::vector<std::string> &args)
{
	return SHOULD_EXIT;
}

CommandManager::CommandManager() {
	this->commands["exit"] = std::make_unique<ExitCommand>();
}

int CommandManager::execute_command(const std::vector<std::string> &args)
{
	if (this->commands.find(args[0]) != commands.end()) {
		return this->commands[args[0]]->execute_command(args);
	}

	return NOT_FOUND;
}
