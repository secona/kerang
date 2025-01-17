extern "C" {
#include "tokenizer.h"
}

#include <gtest/gtest.h>
#include <vector>

class TokenizerTests : public ::testing::Test {
protected:
  struct ExpectedToken {
    TokenType m_type;
    std::string m_value;
    size_t m_len;

    ExpectedToken(TokenType t, const std::string &v)
      : m_type(t)
      , m_value(v) {
      m_len = m_value.size();
    }
  };

  void verifyTokens(
    const std::string &input, const std::vector<ExpectedToken> &expected
  ) {
    TokenArray *arr = tokenize(input.c_str());

    for (size_t i = 0; i < arr->len; i++) {
      Token token = arr->tokens[i];

      EXPECT_EQ(token.type, expected[i].m_type);
      EXPECT_EQ(token.len, expected[i].m_len);

      for (size_t j = 0; j < token.len; j++) {
        EXPECT_EQ(token.value[j], expected[i].m_value[j]);
      }
    }
  }
};

TEST_F(TokenizerTests, HandlesBasicWords) {
  verifyTokens("echo", {{TokenType::Word, "echo"}});
  verifyTokens("cat hello.txt", {{TokenType::Word, "cat"}, {TokenType::Word, "hello.txt"}});
}

TEST_F(TokenizerTests, HandlesQuotedStrings) {
  verifyTokens(
    "echo \"Hello, World!\"",
    {{TokenType::Word, "echo"}, {TokenType::Word, "Hello, World!"}}
  );

  verifyTokens(
    "echo \">>\"",
    {{TokenType::Word, "echo"}, {TokenType::Word, ">>"}}
  );
}

TEST_F(TokenizerTests, HandlesRedirection) {
  verifyTokens(
    "ls -al >> test.txt",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al"},
     {TokenType::Redirection, ">>"},
     {TokenType::Word, "test.txt"}}
  );

  verifyTokens(
    "ls -al>cat.txt",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al"},
     {TokenType::Redirection, ">"},
     {TokenType::Word, "cat.txt"}}
  );

  verifyTokens(
    "ls -al 2>> cat.txt",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al"},
     {TokenType::Redirection, "2>>"},
     {TokenType::Word, "cat.txt"}}
  );

  verifyTokens(
    "ls -al2>> cat.txt",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al2"},
     {TokenType::Redirection, ">>"},
     {TokenType::Word, "cat.txt"}}
  );
}

TEST_F(TokenizerTests, HandlesPipes) {
  verifyTokens(
    "ls -al | grep main.cpp",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al"},
     {TokenType::Pipe, "|"},
     {TokenType::Word, "grep"},
     {TokenType::Word, "main.cpp"}}
  );

  verifyTokens(
    "ls -al|cat.txt",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al"},
     {TokenType::Pipe, "|"},
     {TokenType::Word, "cat.txt"}}
  );
}

TEST_F(TokenizerTests, HandlesCapacity) {
  verifyTokens(
    "ls -al | grep main.cpp >> a.txt >> b.txt >> c.txt >> d.txt",
    {{TokenType::Word, "ls"},
     {TokenType::Word, "-al"},
     {TokenType::Pipe, "|"},
     {TokenType::Word, "grep"},
     {TokenType::Word, "main.cpp"},
     {TokenType::Redirection, ">>"},
     {TokenType::Word, "a.txt"},
     {TokenType::Redirection, ">>"},
     {TokenType::Word, "b.txt"},
     {TokenType::Redirection, ">>"},
     {TokenType::Word, "c.txt"},
     {TokenType::Redirection, ">>"},
     {TokenType::Word, "d.txt"}}
  );
}
