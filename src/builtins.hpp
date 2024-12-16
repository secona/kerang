#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <memory>

enum Status {
	OK = 0,
	SHOULD_EXIT = -1,
	NOT_FOUND = -2,
};

class BuiltinCommand {
public:
	virtual int execute_command(const std::vector<std::string> &args) = 0;
};

class ExitCommand : public BuiltinCommand {
public:
	int execute_command(const std::vector<std::string> &args) override;
};

class CommandManager {
private:
	std::map<std::string, std::unique_ptr<BuiltinCommand>> commands;

public:
	CommandManager();

	int execute_command(const std::vector<std::string> &args);
};
