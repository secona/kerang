#include "parser.h"
#include "tokenizer.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

void test_handlesBasic(void **state) {
    (void)state; // unused
    const char *input = "ls";

    Tokenizer tokenizer = Tokenizer_new(input);
    Command *commands = parse_commands(&tokenizer);

    assert_int_equal(commands->argc, 1);
    assert_string_equal(commands->args[0], "ls");
}

void test_handlesMultiple(void **state) {
    (void)state; // unused
    const char *input = "ls | grep test.txt";

    Tokenizer tokenizer = Tokenizer_new(input);
    Command *commands = parse_commands(&tokenizer);

    assert_int_equal(commands->argc, 1);
    assert_string_equal(commands->args[0], "ls");

    assert_int_equal(commands->next->argc, 2);
    assert_string_equal(commands->next->args[0], "grep");
    assert_string_equal(commands->next->args[1], "test.txt");
}

const struct CMUnitTest parser_tests[] = {
    cmocka_unit_test(test_handlesBasic),
    cmocka_unit_test(test_handlesMultiple),
};

int main() {
    return cmocka_run_group_tests(parser_tests, NULL, NULL);
}
