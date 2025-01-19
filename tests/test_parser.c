#include "parser.h"
#include "tokenizer.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

typedef struct {
    int argc;
    const char *args[256];
} ExpectedCommands;

void verify_commands(const char *input, ExpectedCommands expected[], int command_count) {
    Tokenizer tokenizer = Tokenizer_new(input);
    Command *commands = parse_commands(&tokenizer);
    Command *command = (Command *)malloc(sizeof(Command));
    int i = 0;

    for (command = commands; command != NULL; command = command->next) {
        assert_int_equal(command->argc, expected[i].argc);
        assert_int_equal(command->args[command->argc], NULL);

        for (int j = 0; j < command->argc; j++) {
            assert_string_equal(command->args[j], expected[i].args[j]);
        }

        i++;
    }

    assert_int_equal(i, command_count);
}

void test_handlesBasic(void **state) {
    (void)state; // unused

    ExpectedCommands expected[] = {
        {1, "ls"},
    };
    verify_commands("ls", expected, 1);
}

void test_handlesMultiple(void **state) {
    (void)state; // unused

    ExpectedCommands expected[] = {
        {1, "ls"},
        {2, "grep", "test.txt"}
    };
    verify_commands("ls | grep test.txt", expected, 2);
}

const struct CMUnitTest parser_tests[] = {
    cmocka_unit_test(test_handlesBasic),
    cmocka_unit_test(test_handlesMultiple),
};

int main() {
    return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
