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

void verifyTokens(const char *input, ExpectedToken expected[]) {
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
    } while (token.type != Empty);
}

void test_handlesBasicWords(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {Word, "echo"},
        {Empty, NULL}
    };
    verifyTokens("echo", expected);

    ExpectedToken expected2[] = {
        {Word, "cat"},
        {Word, "hello.txt"},
        {Empty, NULL}
    };
    verifyTokens("cat hello.txt", expected2);
}

void test_handlesQuotedStrings(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {Word, "echo"},
        {Word, "Hello, World!"},
        {Empty, NULL}
    };
    verifyTokens("echo \"Hello, World!\"", expected);

    ExpectedToken expected2[] = {
        {Word, "echo"},
        {Word, ">>"},
        {Empty, NULL}
    };
    verifyTokens("echo \">>\"", expected2);
}

void test_handlesRedirection(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {Word, "ls"},
        {Word, "-al"},
        {Redirection, ">>"},
        {Word, "test.txt"},
        {Empty, NULL}
    };
    verifyTokens("ls -al >> test.txt", expected);

    ExpectedToken expected2[] = {
        {Word, "ls"},
        {Word, "-al"},
        {Redirection, ">"},
        {Word, "cat.txt"},
        {Empty, NULL}
    };
    verifyTokens("ls -al>cat.txt", expected2);

    ExpectedToken expected3[] = {
        {Word, "ls"},
        {Word, "-al"},
        {Redirection, "2>>"},
        {Word, "cat.txt"},
        {Empty, NULL}
    };
    verifyTokens("ls -al 2>> cat.txt", expected3);

    ExpectedToken expected4[] = {
        {Word, "ls"},
        {Word, "-al2"},
        {Redirection, ">>"},
        {Word, "cat.txt"},
        {Empty, NULL}
    };
    verifyTokens("ls -al2>> cat.txt", expected4);
}

void test_handlesPipes(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {Word, "ls"},
        {Word, "-al"},
        {Pipe, "|"},
        {Word, "grep"},
        {Word, "main.cpp"},
        {Empty, NULL}
    };
    verifyTokens("ls -al | grep main.cpp", expected);

    ExpectedToken expected2[] = {
        {Word, "ls"},
        {Word, "-al"},
        {Pipe, "|"},
        {Word, "cat.txt"},
        {Empty, NULL}
    };
    verifyTokens("ls -al|cat.txt", expected2);
}

void test_handlesCapacity(void **state) {
    (void)state; // unused
    ExpectedToken expected[] = {
        {Word, "ls"},
        {Word, "-al"},
        {Pipe, "|"},
        {Word, "grep"},
        {Word, "main.cpp"},
        {Redirection, ">>"},
        {Word, "a.txt"},
        {Redirection, ">>"},
        {Word, "b.txt"},
        {Redirection, ">>"},
        {Word, "c.txt"},
        {Redirection, ">>"},
        {Word, "d.txt"},
        {Empty, NULL}
    };
    verifyTokens(
        "ls -al | grep main.cpp >> a.txt >> b.txt >> c.txt >> d.txt",
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
