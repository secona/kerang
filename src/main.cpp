#include <signal.h>
#include <sys/wait.h>

#include <iostream>
#include <string>
#include <vector>

std::string get_prompt() {
    std::string username = getlogin();

    char hostname[1024];
    gethostname(hostname, 1023);

    char cwd[1024];
    if (getcwd(cwd, 1023) == 0) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }

    return "[" + username + "@" + hostname + " " + cwd + "]> ";
}

void handle_sigint(int sig) {
    std::cout << std::endl
              << "Use 'exit' or Ctrl+D to quit the shell." << std::endl
              << get_prompt();
    std::cout.flush();
}

int main() {
    signal(SIGINT, handle_sigint);

    std::string input;

    while (true) {
        std::cout << get_prompt();

        if (!std::getline(std::cin, input)) {
            break;
        }

        if (input.empty()) {
            continue;
        }
    }
}
