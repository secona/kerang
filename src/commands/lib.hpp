#include <string>
#include <memory>
#include <map>

#include "builtins.hpp"

class CommandManager {
private:
	std::map<std::string, std::unique_ptr<BuiltinCommand>> commands;

public:
	CommandManager();

	int execute_command(const std::vector<std::string> &args);
};
