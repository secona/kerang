#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char *get_prompt() {
    static char prompt[2048];
    char username[512];
    char hostname[512];
    char cwd[512];

    if (getlogin_r(username, sizeof(username)) != 0) {
        perror("getlogin_r() error");
        exit(EXIT_FAILURE);
    }

    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname() error");
        exit(EXIT_FAILURE);
    }

    if (getcwd(cwd, sizeof(cwd)) == 0) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }

    snprintf(prompt, sizeof(prompt), "[%s@%s %s]> ", username, hostname, cwd);

    return prompt;
}

void handle_sigint(int sig) {
    printf("\nUse 'exit' or Ctrl+D to quit the shell.\n%s", get_prompt());
    fflush(stdout);
}

int main() {
    signal(SIGINT, handle_sigint);

    char input[1024];

    while (1) {
        printf("%s", get_prompt());

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
    }

    return 0;
}
