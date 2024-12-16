#include <vector>
#include <string>

std::string get_prompt();

void handle_sigint(int sig);

void execute_command(const std::vector<std::string> &args);
