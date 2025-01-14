#include <iostream>
#include <signal.h>
#include <string>
#include <sys/wait.h>
#include <vector>

std::string getPrompt() {
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

void handleSiging(int sig) {
  std::cout << std::endl
            << "Use 'exit' or Ctrl+D to quit the shell." << std::endl
            << getPrompt();
  std::cout.flush();
}

int main() {
  signal(SIGINT, handleSiging);

  std::string input;

  while (true) {
    std::cout << getPrompt();

    if (!std::getline(std::cin, input)) {
      break;
    }

    if (input.empty()) {
      continue;
    }
  }
}
