#include <iostream>
#include <string>
#include <signal.h>
#include <sstream>
#include <vector>
#include <sys/wait.h>
#include "builtins.hpp"

std::string get_prompt() {
	std::string username = getlogin();

	char hostname[1024];
	gethostname(hostname, 1023);

	char cwd[1024];
	if (getcwd(cwd, 1023) == 0) {
		perror("getcwd() error");
		exit(EXIT_FAILURE);
	};

	return "[" + username + "@" + hostname + " " + cwd + "]> ";
}

void handle_sigint(int sig)
{
	std::cout << std::endl << "Use 'exit' or Ctrl+D to quit the shell." << std::endl;
	std::cout << get_prompt();
	std::cout.flush();
}

void parse_input(const std::string &input, std::vector<std::string> &args)
{
	std::istringstream stream(input);
	std::string token;
	while (stream >> token) {
		args.push_back(token);
	}
}

void execute_command(const std::vector<std::string> &args)
{
	std::vector<char *> argv;
	for (const auto &arg : args) {
		argv.push_back(const_cast<char *>(arg.c_str()));
	}
	argv.push_back(nullptr);

	if (execvp(argv[0], argv.data()) == -1) {
		perror("execvp() failed");
	}
}

int main()
{
	signal(SIGINT, handle_sigint);

	CommandManager cm;
	std::string input;

	while (true) {
		std::cout << get_prompt();
		
		if (!std::getline(std::cin, input)) {
			break;
		}

		if (input.empty()) {
			continue;
		}

		std::vector<std::string> args;
		parse_input(input, args);

		int result = cm.execute_command(args);

		if (result == Status::SHOULD_EXIT) {
			break;
		} else if (result == Status::OK) {
			continue;
		}

		pid_t pid = fork();

		if (pid == 0) {
			execute_command(args);
			exit(EXIT_FAILURE);
		} else if (pid > 0) {
			waitpid(pid, nullptr, 0);
		} else {
			perror("fork() failed");
		}
	}
}
