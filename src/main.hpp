#include <vector>
#include <string>

std::string get_prompt();

void handle_sigint(int sig);

void parse_input(const std::string &input, std::vector<std::string> &args);

void execute_command(const std::vector<std::string> &args);
