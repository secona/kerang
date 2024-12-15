#include <iostream>
#include <string>
#include <signal.h>

#define PROMPT "kerang> "

void handle_sigint(int sig)
{
	std::cout << std::endl << "Use 'exit' or Ctrl+D to quit the shell." << std::endl;
	std::cout << PROMPT;
	std::cout.flush();
}

int main()
{
	signal(SIGINT, handle_sigint);

	std::string input;

	while (true) {
		std::cout << PROMPT;
		
		if (!std::getline(std::cin, input)) {
			break;
		}

		if (input == "exit") {
			break;
		}

		if (input.empty()) {
			continue;
		}

		std::cout << input << std::endl;
	}
}
