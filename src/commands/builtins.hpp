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

class ChangeDirectoryCommand : public BuiltinCommand {
public:
	int execute_command(const std::vector<std::string> &args) override;
};
