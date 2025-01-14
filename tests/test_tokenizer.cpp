#include "tokenizer.hpp"

#include <gtest/gtest.h>

class TokenizerTests : public ::testing::Test {
protected:
  struct ExpectedToken {
    TokenType type;
    std::string value;

    ExpectedToken(TokenType t, const std::string &v)
      : type(t)
      , value(v) {
    }
  };

  void verifyTokens(
    const std::string &input, const std::vector<ExpectedToken> &expected
  ) {
    Tokenizer tokenizer(input);
    std::vector<Token> tokens = tokenizer.tokenize();
    ASSERT_EQ(tokens.size(), expected.size());

    for (size_t i = 0; i < tokens.size(); i++) {
      EXPECT_EQ(tokens[i].type, expected[i].type)
        << "Token " << i << " type mismatch";
      EXPECT_STREQ(tokens[i].value.c_str(), expected[i].value.c_str())
        << "Token " << i << " value mismatch";
    }
  }
};

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
