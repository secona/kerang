#ifndef KERANG_MAIN_HPP_
#define KERANG_MAIN_HPP_

#include <vector>
#include <string>

std::string get_prompt();

void handle_sigint(int sig);

void execute_command(const std::vector<std::string> &args);

#endif
