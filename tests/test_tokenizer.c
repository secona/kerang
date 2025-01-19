#include "tokenizer.h"

#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <cmocka.h>

typedef struct {
    TokenType type;
    const char *value;
} ExpectedToken;

void verify_tokens(const char *input, ExpectedToken expected[]) {
    Tokenizer tokenizer = Tokenizer_new(input);
    Token token;
    size_t i = 0;

    do {
        token = Tokenizer_next(&tokenizer);
        assert_int_equal(token.type, expected[i].type);
        if (expected[i].value)
            assert_string_equal(token.value, expected[i].value);
        else
            assert_null(token.value);
        i++;
    } while (token.type != TOKEN_EMPTY);
}

void test_handlesBasicWords(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {TOKEN_WORD, "echo"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("echo", expected);

    ExpectedToken expected2[] = {
        {TOKEN_WORD, "cat"},
        {TOKEN_WORD, "hello.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("cat hello.txt", expected2);
}

void test_handlesQuotedStrings(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {TOKEN_WORD, "echo"},
        {TOKEN_WORD, "Hello, World!"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("echo \"Hello, World!\"", expected);

    ExpectedToken expected2[] = {
        {TOKEN_WORD, "echo"},
        {TOKEN_WORD, ">>"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("echo \">>\"", expected2);
}

void test_handlesRedirection(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_REDIR, ">>"},
        {TOKEN_WORD, "test.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("ls -al >> test.txt", expected);

    ExpectedToken expected2[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_REDIR, ">"},
        {TOKEN_WORD, "cat.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("ls -al>cat.txt", expected2);

    ExpectedToken expected3[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_REDIR, "2>>"},
        {TOKEN_WORD, "cat.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("ls -al 2>> cat.txt", expected3);

    ExpectedToken expected4[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al2"},
        {TOKEN_REDIR, ">>"},
        {TOKEN_WORD, "cat.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("ls -al2>> cat.txt", expected4);
}

void test_handlesPipes(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_PIPE, "|"},
        {TOKEN_WORD, "grep"},
        {TOKEN_WORD, "main.cpp"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("ls -al | grep main.cpp", expected);

    ExpectedToken expected2[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_PIPE, "|"},
        {TOKEN_WORD, "cat.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens("ls -al|cat.txt", expected2);
}

void test_handlesCapacity(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_PIPE, "|"},
        {TOKEN_WORD, "grep"},
        {TOKEN_WORD, "main.cpp"},
        {TOKEN_REDIR, ">>"},
        {TOKEN_WORD, "a.txt"},
        {TOKEN_REDIR, ">>"},
        {TOKEN_WORD, "b.txt"},
        {TOKEN_REDIR, ">>"},
        {TOKEN_WORD, "c.txt"},
        {TOKEN_REDIR, ">>"},
        {TOKEN_WORD, "d.txt"},
        {TOKEN_EMPTY, NULL}
    };
    verify_tokens(
        "ls -al | grep main.cpp >> a.txt >> b.txt >> c.txt >> d.txt",
        expected
    );
}

void test_handlesSemicolons(void **state) {
    (void)state;

    ExpectedToken expected[] = {
        {TOKEN_WORD, "ls"},
        {TOKEN_WORD, "-al"},
        {TOKEN_SEMICOLON, ";"},
        {TOKEN_WORD, "cat"},
        {TOKEN_WORD, "test.txt"},
        {TOKEN_SEMICOLON, ";"},
        {TOKEN_WORD, "vim"},
        {TOKEN_WORD, "hello.txt"},
    };
    verify_tokens(
        "ls -al; cat test.txt; vim hello.txt",
        expected
    );
}

const struct CMUnitTest tokenizer_tests[] = {
    cmocka_unit_test(test_handlesBasicWords),
    cmocka_unit_test(test_handlesQuotedStrings),
    cmocka_unit_test(test_handlesRedirection),
    cmocka_unit_test(test_handlesPipes),
    cmocka_unit_test(test_handlesCapacity),
};

int main() {
    return cmocka_run_group_tests(tokenizer_tests, NULL, NULL);
}
